/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:12:00 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/01 17:39:59 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	give_forks(t_philo *philo, t_mtx *forks, int philo_position)
{
	long	nbr_philos;

	nbr_philos = philo->program->philo_nbr;
	philo->first_fork = &forks[(philo_position + 1) % nbr_philos];
	philo->second_fork = &forks[philo_position];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % nbr_philos];
	}
}

static void	init_philo(t_program *data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < data->philo_nbr)
	{
		philo = data->philos + i;
		philo->id = i + 1;
		philo->is_full = 0;
		philo->meals_eaten = 0;
		philo->program = data;
		pthread_mutex_init(&philo->philo_mtx, NULL);
		pthread_mutex_init(&philo->check_threads_mutex, NULL);
		give_forks(philo, data->forks, i);
	}
}

void	init_data(t_program *data)
{
	int	i;

	i = -1;
	data->end_of_program = false;
	data->threads_ready = false;
	data->all_full = 0;
	pthread_mutex_init(&data->data_mutex, NULL);
	pthread_mutex_init(&data->write_mutex, NULL);
	data->philos = malloc(sizeof(t_philo) * data->philo_nbr);
	if (!data->philos)
		exit_when_error("Malloc error !\n");
	data->forks = malloc(sizeof(t_mtx) * data->philo_nbr);
	if (!data->forks)
		exit_when_error("Malloc error !\n");
	while (++i < data->philo_nbr)
	{
		pthread_mutex_init(&data->forks[i], NULL);
	}
	init_philo(data);
}
