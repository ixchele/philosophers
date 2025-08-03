/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 17:02:09 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/03 17:02:11 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	think_action(t_philo *philo)
{
	print_status(philo, THINK);
	if ((philo->program->philo_nbr % 2 != 0))
		usleep(1000);
}

void	eat_action(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	print_status(philo, FORK);
	pthread_mutex_lock(philo->second_fork);
	print_status(philo, FORK);
	set_long(&philo->philo_mtx, &philo->last_eating_time, get_current_time());
	print_status(philo, EAT);
	ft_usleep(philo->program->time_to_eat);
	philo->meals_eaten++;
	if (philo->program->num_of_meals > 0
		&& philo->meals_eaten == philo->program->num_of_meals)
	{
		set_bool(&philo->philo_mtx, &philo->is_full, true);
		increment(&philo->program->data_mutex, &philo->program->all_full);
	}
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
}

void	sleep_action(t_philo *philo)
{
	print_status(philo, SLEEP);
	ft_usleep(philo->program->time_to_sleep);
}
