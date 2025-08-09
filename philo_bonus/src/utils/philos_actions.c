/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:31:51 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/04 17:05:49 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	eat_action(t_philo *philo)
{
	sem_wait(philo->program->forks_sem->sem);
	print_status(philo, FORK);
	sem_wait(philo->program->forks_sem->sem);
	print_status(philo, FORK);
	set_long(philo->value_sem->sem, &philo->last_eating_time,
		get_current_time());
	print_status(philo, EAT);
	ft_usleep(philo->program->time_to_eat);
	sem_post(philo->program->forks_sem->sem);
	sem_post(philo->program->forks_sem->sem);
	philo->meals_eaten++;
	if (philo->program->num_of_meals > 0
		&& philo->meals_eaten == philo->program->num_of_meals)
		set_bool(philo->meal_sem->sem, &philo->is_full, true);
}

void	sleep_action(t_philo *philo)
{
	print_status(philo, SLEEP);
	ft_usleep(philo->program->time_to_sleep);
}

void	think_action(t_philo *philo)
{
	print_status(philo, THINK);
	if ((philo->program->philo_nbr % 2 != 0))
		usleep(1000);
}
