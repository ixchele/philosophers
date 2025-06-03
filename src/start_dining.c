/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dining.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:35:35 by zbengued          #+#    #+#             */
/*   Updated: 2025/05/27 14:37:45 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	check_if_all_full(t_rules *rules)
{
	long	i;

	i = 0;
	while (i < rules->nb_of_philos)
	{
		pthread_mutex_lock(&rules->philos[i].meal_eat_mut);
		if (rules->philos[i].meals_eaten != rules->max_meal)
		{
			pthread_mutex_unlock(&rules->philos[i].meal_eat_mut);
			return (false);
		}
		pthread_mutex_unlock(&rules->philos[i].meal_eat_mut);
		i++;
	}
	return (true);
}

static void	*check_if_philo_dead_or_full(void *arg)
{
	t_rules	*rules;
	long	i;

	rules = (t_rules *)arg;
	while (!simulation_end(rules))
	{
		i = 0;
		while (i < rules->nb_of_philos && !simulation_end(rules))
		{
			pthread_mutex_lock(&rules->philos[i].last_meal_mutex);
			if (get_time() - rules->philos[i].last_meal > rules->time_to_die)
			{
				// ph_sleep(500, rules);
				print_philo_action(&rules->philos[i], "died");
				mark_as_dead(rules);
				// printf("%lld %ld %s\n",get_time() - rules->philos[i].rules->start_time, rules->philos[i].id, "died");
			}
			pthread_mutex_unlock(&rules->philos[i].last_meal_mutex);
			i++;
		}
		if (check_if_all_full(rules))
			mark_as_full(rules);
		// ph_sleep(1000, rules);
	}
	return (NULL);
}

void	*philo_loop(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	// if ((philo->id % 2) != 0)
	// 	usleep(500);
	while (!simulation_end(philo->rules))
	{
		philo_eat(philo);
		if (check_death_flag(philo->rules))
			break ;
		philo_sleep(philo);
		if (check_death_flag(philo->rules))
			break ;
		philo_think(philo);
		ph_sleep(500, philo->rules);
	}
	return (NULL);
}

void	start_the_dining(t_rules *rules)
{
	long		i;
	pthread_t	death_cheker;

	i = 0;
	rules->start_time = get_time();
	while (i < rules->nb_of_philos)
	{
		pthread_mutex_lock(&rules->philos[i].last_meal_mutex);
		rules->philos[i].last_meal = rules->start_time;
		pthread_mutex_unlock(&rules->philos[i].last_meal_mutex);
		pthread_create(&rules->philos[i].thread_id,
				 NULL, philo_loop, &rules->philos[i]);
		i++;
	}
	pthread_create(&death_cheker, NULL, check_if_philo_dead_or_full, rules);
	i = 0;
	while (i < rules->nb_of_philos)
	{
		pthread_join(rules->philos[i].thread_id, NULL);
		i++;
	}
	pthread_join(death_cheker, NULL);
}
