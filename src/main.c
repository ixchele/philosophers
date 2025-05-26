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

long long	get_time(void)
{
	struct timeval	timev;

	gettimeofday(&timev, NULL);
	return ((timev.tv_sec * 1000LL) + (timev.tv_usec / 1000));
}

void	print_philo_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->rules->mutex[PRINT]);
	if (!philo->rules->philo_died)
		printf("%lld %ld %s\n",get_time() - philo->rules->start_time, philo->id, action);
	pthread_mutex_unlock(&philo->rules->mutex[PRINT]);
}

bool	check_dead_flag(t_rules *rules)
{
	bool dead;

	pthread_mutex_lock(&rules->mutex[DEATH]);
	dead = rules->philo_died;
	pthread_mutex_unlock(&rules->mutex[DEATH]);
	return dead;
}

void mark_as_dead(t_rules *rules)
{
	pthread_mutex_lock(&rules->mutex[DEATH]);
	rules->philo_died = true;
	pthread_mutex_unlock(&rules->mutex[DEATH]);
}

void	ph_sleep(long long time_ms, t_rules *rules)
{
	long long	start;

	start = get_time();
	while (!check_dead_flag(rules))
	{
		if (get_time() - start >= time_ms)
			break ;
		usleep(100);
	}
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_t *first;
	pthread_mutex_t *second;

	if (philo->left_fork < philo->right_fork)
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	else
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	pthread_mutex_lock(first);
	print_philo_action(philo, "has taken a fork");
	pthread_mutex_lock(second);
	print_philo_action(philo, "has taken a fork");
	print_philo_action(philo, "is eating");
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	ph_sleep(philo->rules->time_to_eat, philo->rules);
	philo->meals_eaten++;
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
}

// void	philo_eat(t_philo *philo)
// {
// 	pthread_mutex_lock(philo->right_fork);
// 	print_philo_action(philo, "has taken a fork");
// 	pthread_mutex_lock(philo->left_fork);
// 	print_philo_action(philo, "has taken a fork");
// 	print_philo_action(philo, "is eating");
// 	pthread_mutex_lock(&philo->last_meal_mutex);
// 	philo->last_meal = get_time();
// 	pthread_mutex_unlock(&philo->last_meal_mutex);
// 	ph_sleep(philo->rules->time_to_eat, philo->rules);
// 	philo->meals_eaten++;	
// 	pthread_mutex_unlock(philo->left_fork);
// 	pthread_mutex_unlock(philo->right_fork);
// }

void	philo_sleep(t_philo *philo)
{
	print_philo_action(philo, "is sleeping");
	ph_sleep(philo->rules->time_to_sleep, philo->rules);
}

void	philo_think(t_philo *philo)
{
	// TODO : should think the time that is left for him to die !
	print_philo_action(philo, "is thinking");
	pthread_mutex_lock(&philo->last_meal_mutex);
	ph_sleep(philo->rules->time_to_die - philo->last_meal, philo->rules);
	pthread_mutex_unlock(&philo->last_meal_mutex);
}


void	*philo_loop(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if ((philo->id % 2) != 0)
		usleep(500);
	while (!check_dead_flag(philo->rules))
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
				print_philo_action(&rules->philos[i], "est mort");
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

int	main(int ac, char **av)
{
	t_rules	rules;

	if (ac != 5 && ac != 6)
		return (print_usage(), -1);
	if (!parse_args(&rules, ac, av))
		return (printf("parse error\n"), -1);
	if (!init_all(&rules))
		return (printf("error in initialisation"), -1);
	start_the_dining(&rules);
	// printf("nb_of_philosophers ; %ld\n", ph_atol(av[1]));
	// printf("time_to_die ; %ld\n", ph_atol(av[2]));
	// printf("time_to_eat ; %ld\n", ph_atol(av[3]));
	// printf("time_to_sleep ; %ld\n", ph_atol(av[4]));
	// if (ac == 6)
	// 	printf("nb_of_times_each_philosopher_must_eat ; %ld\n", ph_atol(av[5]));
}
