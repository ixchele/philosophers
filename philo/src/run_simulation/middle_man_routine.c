/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   middle_man_routine.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:20:55 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/03 16:32:05 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static bool	check_dead_flag(t_philo *philo)
{
	long	time_passed;
	long	time_to_die;
	long	last_eating_time;

	if (read_bool(&philo->philo_mtx, &philo->is_full) == true)
		return (0);
	last_eating_time = read_long(&philo->philo_mtx, &philo->last_eating_time);
	time_passed = get_current_time() - last_eating_time;
	time_to_die = philo->program->time_to_die;
	if (time_passed > time_to_die)
		return (1);
	return (0);
}

void	*middle_man_routine(void *param)
{
	t_program	*data;
	int			i;

	data = (t_program *)param;
	while (get_current_time() < data->start_dinner)
		usleep(500);
	ft_usleep(data->time_to_die);
	while (!end_of_simulation(data) && !all_philos_full(data))
	{
		i = -1;
		while ((++i < data->philo_nbr && !end_of_simulation(data))
			&& !all_philos_full(data))
		{
			if (check_dead_flag(data->philos + i) == true
				&& !all_philos_full(data))
			{
				set_bool(&data->data_mutex, &data->end_of_program, true);
				usleep(1000);
				print_status(data->philos + i, DIE);
			}
			usleep(4000);
		}
	}
	return (NULL);
}
