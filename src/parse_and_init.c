/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:11:29 by zbengued          #+#    #+#             */
/*   Updated: 2025/05/28 16:18:35 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <pthread.h>

bool	parse_args(t_rules *rules, int ac, char **av)
{
	long	*fields;
	int		i;

	fields = (long *)rules;
	i = 0;
	if (ac != 5 && ac != 6)
		return (false);
	rules->max_meal = -2;
	rules->nb_of_philos = ph_atol(av[1]);
	rules->time_to_die = ph_atol(av[2]);
	rules->time_to_eat = ph_atol(av[3]);
	rules->time_to_sleep = ph_atol(av[4]);
	if (ac == 6)
		rules->max_meal = ph_atol(av[5]);
	while (i < 5)
	{
		if (fields[i] == -1)
			return (false);
		i++;
	}
	return (true);
}

static bool	init_mutex(t_rules *rules)
{
	long	i;

	i = 0;
	rules->middleman = malloc(sizeof(t_middleman));
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->nb_of_philos);
	rules->mutex = malloc(sizeof(pthread_mutex_t) * 3);
	if (!rules->mutex || !rules->forks || !rules->middleman)
		return (false);
	rules->middleman->taken = malloc(sizeof(bool) * rules->nb_of_philos);
	rules->middleman->forks = malloc(sizeof(pthread_mutex_t *) * rules->nb_of_philos);
	if (!rules->middleman->taken || !rules->middleman->forks)
		return (false);
	while (i < rules->nb_of_philos)
	{
		if (pthread_mutex_init(&rules->forks[i], NULL))
			return (false);
		rules->middleman->forks[i] = &rules->forks[i];
		rules->middleman->taken[i] = false;
		i++;
	}
	if (pthread_mutex_init(&rules->mutex[PRINT], NULL)
		|| pthread_mutex_init(&rules->mutex[DEATH], NULL)
		|| pthread_mutex_init(&rules->mutex[FULLNESS], NULL)
		|| pthread_mutex_init(&rules->middleman->taken_mut, NULL))
		return (false);
	return (true);
}

static bool	init_philos(t_rules *rules)
{
	long	i;

	i = 0;
	rules->philos = malloc((sizeof(t_philo) * rules->nb_of_philos));
	if (!rules->philos)
		return (false);
	while (i < rules->nb_of_philos)
	{
		rules->philos[i].id = i + 1;
		rules->philos[i].meals_eaten = 0;
		rules->philos[i].last_meal = 0;
		rules->philos[i].left_fork = &rules->forks[i];
		rules->philos[i].right_fork = &rules->forks[(i + 1)
			% rules->nb_of_philos];
		if (pthread_mutex_init(&rules->philos[i].last_meal_mutex, NULL)
			|| pthread_mutex_init(&rules->philos[i].can_eat_mutex, NULL)
			|| pthread_mutex_init(&rules->philos[i].meal_eat_mut, NULL))
			return (false);
		rules->philos[i].rules = (t_rules *)rules;
		rules->philos[i].can_eat = false;
		i++;
	}
	return (true);
}

bool	init_all(t_rules *rules)
{
	rules->philo_died = false;
	rules->philo_full = false;
	if (!init_mutex(rules) || !init_philos(rules))
		return (false);
	return (true);
}
