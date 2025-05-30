/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_action.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:38:45 by zbengued          #+#    #+#             */
/*   Updated: 2025/05/27 14:41:26 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	philo_eat(t_philo *philo)
{
	pthread_mutex_t *first;
	pthread_mutex_t *second;

	if (philo->left_fork == philo->right_fork)
	{
		pthread_mutex_lock(philo->left_fork);
		print_philo_action(philo, "has taken a fork");
		ph_sleep(philo->rules->time_to_die, philo->rules);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
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

void	philo_sleep(t_philo *philo)
{
	print_philo_action(philo, "is sleeping");
	ph_sleep(philo->rules->time_to_sleep, philo->rules);
}

void	philo_think(t_philo *philo)
{
	// TODO : should think the time that is left for him to die !
	long long time_since_meal;
	long long time_to_think;

	print_philo_action(philo, "is thinking");
	pthread_mutex_lock(&philo->last_meal_mutex);
	time_since_meal = get_time() - philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	time_to_think = philo->rules->time_to_die - time_since_meal
		- philo->rules->time_to_eat;
	if (time_to_think < 0)
		time_to_think = 0;
	ph_sleep(time_to_think, philo->rules);
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
