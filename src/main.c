/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:58:33 by zbengued          #+#    #+#             */
/*   Updated: 2025/05/24 17:51:30 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <pthread.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>


// TODO : 
// [x] parse_args()
// [x] init_all()
// [] start_simulation()
// [] destroy_all()
// -----------------
static void	print_usage(void)
{
	printf("Usage ; ./philo [number_of_philosophers] ");
	printf("[time_to_die] [time_to_eat] [time_to_sleep] ");
	printf("(optional argument ");
	printf("[number_of_times_each_philosopher_must_eat])\n");
}

void	print_philo_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(philo->rules->print_mutex);
	if (!philo->rules->philo_died)
		printf("philo number %ld %s\n", philo->id, action);
	pthread_mutex_unlock(philo->rules->print_mutex);
}

long long	get_time(void)
{
	struct timeval	timev;

	gettimeofday(&timev, NULL);
	return ((timev.tv_sec * 1000LL) + (timev.tv_usec / 1000));
}

void	ph_sleep(long long time_ms, t_rules *rules)
{
	long long	start;

	start = get_time();
	while (!rules->philo_died)
	{
		if (get_time() - start >= time_ms)
			break ;
		usleep(100);
	}
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_philo_action(philo, "a prit une fourchette");
	pthread_mutex_lock(philo->left_fork);
	print_philo_action(philo, "a prit une fourchette");
	print_philo_action(philo, "est entrain de manger");
	philo->last_meal = get_time();
	ph_sleep(philo->rules->time_to_eat, philo->rules);
	philo->meals_eaten++;	
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_sleep(t_philo *philo)
{
	print_philo_action(philo, "dort");
	ph_sleep(philo->rules->time_to_sleep, philo->rules);
}

void	philo_think(t_philo *philo)
{
	// TODO : should think the time that is left for him to die !
	print_philo_action(philo, "panse");
}

bool	check(t_philo *philo)
{
	bool dead;

	pthread_mutex_lock(philo->rules->death_mutex);
	dead = philo->rules->philo_died;
	pthread_mutex_unlock(philo->rules->death_mutex);
	return dead;
}

void kill(t_philo *philo)
{
	pthread_mutex_lock(philo->rules->death_mutex);
	philo->rules->philo_died = true;
	pthread_mutex_unlock(philo->rules->death_mutex);
}

void	*philo_loop(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if ((philo->id % 2) != 0)
		usleep(500);
	while (check(philo))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	*check_if_philo_dead(void *arg)
{
	t_rules	*rules;

	rules = (t_rules *)arg;
	while (!rules->philo_died)
	{
		
	}
}

void	start_the_dining(t_rules *rules)
{
	long	i;

	i = 0;
	rules->start_time = get_time();
	while (i < rules->nb_of_philos)
	{
		rules->philos[i].last_meal = rules->start_time;
		pthread_create(&rules->philos[i].thread_id,
				 NULL, philo_loop, &rules->philos[i]);
		i++;
	}
	i = 0;
	while (i < rules->nb_of_philos)
	{
		pthread_join(rules->philos[i].thread_id, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_rules	rules;

	if (ac != 5 && ac != 6)
		return (print_usage(), -1);
	if (!parse_args(&rules, ac, av))
		return (printf("parse error\n"), -1);
	if (!init_all(&rules))
		return (printf("error in initialisation"), -1);
	printf("nb_of_philosophers ; %ld\n", ph_atol(av[1]));
	printf("time_to_die ; %ld\n", ph_atol(av[2]));
	printf("time_to_eat ; %ld\n", ph_atol(av[3]));
	printf("time_to_sleep ; %ld\n", ph_atol(av[4]));
	if (ac == 6)
		printf("nb_of_times_each_philosopher_must_eat ; %ld\n", ph_atol(av[5]));
}
