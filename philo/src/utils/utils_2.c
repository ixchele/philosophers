/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 17:46:18 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/03 17:00:59 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long	get_current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		printf("gettimeofday() error \n");
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

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
	long		time_passed;
	static char	*messages[] = {
		"%-6ld %d "COLOR_CYAN"has taken a fork"COLOR_RESET"\n",
		"%-6ld %d is "COLOR_YELLOW"eating"COLOR_RESET"\n",
		"%-6ld %d is "COLOR_BLUE"sleeping"COLOR_RESET"\n",
		"%-6ld %d is "COLOR_GREEN"thinking"COLOR_RESET"\n",
		"%-6ld %d "COLOR_RED"died"COLOR_RESET"\n"
	};

	pthread_mutex_lock(&philo->program->data_mutex);
	time_passed = get_current_time() - philo->program->start_dinner;
	pthread_mutex_unlock(&philo->program->data_mutex);
	if (read_bool(&philo->program->data_mutex, &philo->is_full) == true)
		return ;
	pthread_mutex_lock(&philo->program->write_mutex);
	if (!end_of_simulation(philo->program))
		printf(messages[state - 1], time_passed, philo->id);
	pthread_mutex_unlock(&philo->program->write_mutex);
}

bool	all_philos_full(t_program *data)
{
	long	nbr;

	nbr = read_long(&data->data_mutex, &data->all_full);
	if (nbr == data->philo_nbr)
		return (1);
	return (false);
}

void	clean_exit(t_program *data)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < data->philo_nbr)
	{
		philo = data->philos + i;
		pthread_mutex_destroy(&philo->philo_mtx);
	}
	pthread_mutex_destroy(&data->data_mutex);
	pthread_mutex_destroy(&data->write_mutex);
	free(data->philos);
	free(data->forks);
}
