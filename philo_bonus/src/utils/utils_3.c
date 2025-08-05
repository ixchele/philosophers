/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils-v3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:08:23 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/04 16:19:51 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

int	open_sems(t_philo *philo)
{
	philo->local_sem = malloc(sizeof(t_named_semaphores));
	if (!philo->local_sem)
		return (-1);
	philo->meal_sem = malloc(sizeof(t_named_semaphores));
	if (!philo->meal_sem)
		return (-1);
	philo->value_sem = malloc(sizeof(t_named_semaphores));
	if (!philo->value_sem)
		return (-1);
	if (ft_sem_open(&philo->local_sem, "local", philo->id))
		return (-1);
	if (ft_sem_open(&philo->meal_sem, "meal", philo->id))
		return (-1);
	if (ft_sem_open(&philo->value_sem, "value", philo->id))
		return (-1);
	return (0);
}

bool	end_of_dinner(t_program *data)
{
	long	x;

	x = check_death(data->die_sem->sem, data->global_sem->sem);
	if (x == 0 || x > 1)
		return (true);
	else
		return (false);
}

void	exit_when_error(char *str)
{
	printf("%s", str);
	exit(EXIT_FAILURE);
}
