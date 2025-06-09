/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_action.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:38:45 by zbengued          #+#    #+#             */
/*   Updated: 2025/06/03 15:48:29 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static bool	one_philo(t_philo *philo)
{
	if (philo->left_fork == philo->right_fork)
	{
		pthread_mutex_lock(philo->left_fork);
		print_philo_action(philo, "has taken a fork");
		ph_sleep(philo->rules->time_to_die * 1000, philo->rules);
		pthread_mutex_unlock(philo->left_fork);
		return (true);
	}
	return (false);
}

static void	eating(t_philo *philo,
			pthread_mutex_t *first, pthread_mutex_t *second)
{
	pthread_mutex_lock(first);
	print_philo_action(philo, "has taken a fork");
	pthread_mutex_lock(second);
	print_philo_action(philo, "has taken a fork");
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_time();
	print_philo_action(philo, "is eating");
	pthread_mutex_unlock(&philo->last_meal_mutex);
	ph_sleep(philo->rules->time_to_eat * 1000, philo->rules);
	pthread_mutex_lock(&philo->meal_eat_mut);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_eat_mut);
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (one_philo(philo))
		return ;
	if (philo->id % 2 == 0)
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	else
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	eating(philo, first, second);
}

void	philo_sleep(t_philo *philo)
{
	print_philo_action(philo, "is sleeping");
	ph_sleep(philo->rules->time_to_sleep * 1000, philo->rules);
}

void	philo_think(t_philo *philo)
{
	long long	time_since_meal;
	long long	time_to_think;

	print_philo_action(philo, "is thinking");
	pthread_mutex_lock(&philo->last_meal_mutex);
	time_since_meal = get_time() - philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	time_to_think = philo->rules->time_to_die - time_since_meal
		- philo->rules->time_to_eat;
	if (time_to_think < 0)
		time_to_think = 0;
	ph_sleep(time_to_think * 1000, philo->rules);
}
