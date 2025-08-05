/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:08:18 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/04 17:05:08 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

int	ft_usleep(long time)
{
	long	start;

	start = get_current_time();
	while ((get_current_time() - start) < time)
		usleep(time / 10);
	return (0);
}

void	print_status(t_philo *philo, int state)
{
	long	time_passed;

	sem_wait(philo->program->global_sem->sem);
	time_passed = get_current_time() - philo->program->start_dinner;
	sem_post(philo->program->global_sem->sem);
	if (read_bool(philo->meal_sem->sem, &philo->is_full) == true)
		return ;
	sem_wait(philo->local_sem->sem);
	if (state == FORK && !end_of_dinner(philo->program))
		printf("%-6ld %d has taken a fork\n", time_passed, philo->id);
	if (state == EAT && !end_of_dinner(philo->program))
		printf("%-6ld %d is eating\n", time_passed, philo->id);
	if (state == SLEEP && !end_of_dinner(philo->program))
		printf("%-6ld %d is sleeping\n", time_passed, philo->id);
	if (state == THINK && !end_of_dinner(philo->program))
		printf("%-6ld %d is thinking\n", time_passed, philo->id);
	if (state == DIE)
		printf("%-6ld %d died\n", time_passed, philo->id);
	sem_post(philo->local_sem->sem);
}

static void	close_unlink(t_named_semaphores *sem, bool mode)
{
	if (!sem || !sem->sem || !sem->name)
	{
		if (sem)
			free(sem);
		return ;
	}
	sem_close(sem->sem);
	if (mode)
		sem_unlink(sem->name);
	free(sem->name);
	free(sem);
}

static void	unlink_semaphores(t_program *data, bool mode)
{
	close_unlink(data->die_sem, mode);
	close_unlink(data->forks_sem, mode);
	close_unlink(data->global_sem, mode);
	close_unlink(data->end_prog_sem, mode);
	close_unlink(data->philos.local_sem, mode);
	close_unlink(data->philos.meal_sem, mode);
	close_unlink(data->philos.value_sem, mode);
}

void	clean_up(t_program *data, unsigned int exit_num, bool mode)
{
	unlink_semaphores(data, mode);
	free(data->pids);
	exit(exit_num);
}
