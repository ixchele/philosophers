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

static void	*check_if_philo_dead(void *arg)
{
	t_rules	*rules;
	long	i;

	rules = (t_rules *)arg;
	while (!check_dead_flag(rules))
	{
		i = 0;
		while (i < rules->nb_of_philos && !check_dead_flag(rules))
		{
			pthread_mutex_lock(&rules->philos[i].last_meal_mutex);
			if (get_time() - rules->philos[i].last_meal > rules->time_to_die)
			{
				print_philo_action(&rules->philos[i], "is died");
				mark_as_dead(rules);
			}
			pthread_mutex_unlock(&rules->philos[i].last_meal_mutex);
			i++;
		}
		usleep(1000);
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
	pthread_create(&death_cheker, NULL, check_if_philo_dead, rules);
	i = 0;
	while (i < rules->nb_of_philos)
	{
		pthread_join(rules->philos[i].thread_id, NULL);
		i++;
	}
	pthread_join(death_cheker, NULL);
}
