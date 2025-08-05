/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:07:12 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/04 16:35:58 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

static void	*start_simulation(t_philo *philo)
{
	if (open_sems(philo))
		clean_up(philo->program, 1, 0);
	while (get_current_time() < philo->program->start_dinner)
		usleep(500);
	if (philo->id % 2 == 0)
		usleep(1000);
	pthread_create(&philo->thread, NULL, &admin_routine, philo);
	philo->last_eating_time = get_current_time();
	while (!end_of_dinner(philo->program))
	{
		if (read_bool(philo->meal_sem->sem, &philo->is_full) == true)
			break ;
		eat_action(philo);
		sleep_action(philo);
		think_action(philo);
	}
	pthread_join(philo->thread, NULL);
	clean_up(philo->program, 0, 0);
	return (NULL);
}

static void	*check_wait(void *data)
{
	t_wait	*wait;
	int		x;

	x = 0;
	wait = data;
	while (read_bool(wait->stop, &wait->stop_flag))
	{
		if (wait->died->__align == 0 || wait->died->__align > 1)
		{
			usleep(2000);
			while (x < wait->pids_num)
			{
				kill(wait->pids[x], SIGKILL);
				x++;
			}
			break ;
		}
	}
	return (NULL);
}

void	prepare_simulation(t_program *data)
{
	pthread_t	thread;
	t_wait		wait;
	int			i;

	i = -1;
	data->start_dinner = get_current_time() + (data->philo_nbr * 25);
	while (++i < data->philo_nbr)
	{
		data->philos.id = i + 1;
		data->pids[i] = fork();
		if (data->pids[i] == 0)
			start_simulation(&data->philos);
	}
	wait.died = data->die_sem->sem;
	wait.stop = data->end_prog_sem->sem;
	wait.stop_flag = true;
	wait.pids = data->pids;
	wait.pids_num = data->philo_nbr;
	pthread_create(&thread, NULL, &check_wait, &wait);
	while (waitpid(-1, NULL, 0) != -1)
		;
	set_bool(data->end_prog_sem->sem, &wait.stop_flag, 0);
	pthread_join(thread, NULL);
}
