/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 17:44:43 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/03 17:02:35 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	*handle_one_philo(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (get_current_time() < philo->program->start_dinner)
		usleep(500);
	set_long(&philo->philo_mtx, &philo->last_eating_time, get_current_time());
	print_status(philo, FORK);
	while (!end_of_simulation(philo->program))
		ft_usleep(0);
	return (NULL);
}

void	*start_simulation(void *params)
{
	t_philo	*philo;

	philo = (t_philo *)params;
	while (get_current_time() < philo->program->start_dinner)
		usleep(500);
	if (philo->id % 2 == 0)
		usleep(1000);
	philo->last_eating_time = get_current_time();
	while (!end_of_simulation(philo->program)
		&& !all_philos_full(philo->program))
	{
		if (philo->is_full == true)
			break ;
		eat_action(philo);
		sleep_action(philo);
		think_action(philo);
	}
	return (NULL);
}

void	prepare_simulation(t_program *data)
{
	int	i;

	i = -1;
	if (data->num_of_meals == 0)
		return ;
	else if (data->philo_nbr == 1)
	{
		data->start_dinner = (get_current_time() + data->philo_nbr * 25);
		pthread_create(&data->philos[0].thread_id, NULL, handle_one_philo,
			&data->philos[0]);
	}
	else
	{
		data->start_dinner = (get_current_time() + data->philo_nbr * 25);
		while (++i < data->philo_nbr)
			pthread_create(&data->philos[i].thread_id, NULL, start_simulation,
				&data->philos[i]);
	}
	pthread_create(&data->admin_thread, NULL, middle_man_routine, data);
	i = -1;
	while (++i < data->philo_nbr)
		pthread_join(data->philos[i].thread_id, NULL);
	pthread_join(data->admin_thread, NULL);
	set_bool(&data->data_mutex, &data->end_of_program, true);
}
