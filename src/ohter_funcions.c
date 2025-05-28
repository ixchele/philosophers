/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ohter_funcions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:10:29 by zbengued          #+#    #+#             */
/*   Updated: 2025/05/28 15:11:01 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	check_dead_flag(t_rules *rules)
{
	bool dead;

	pthread_mutex_lock(&rules->mutex[DEATH]);
	dead = rules->philo_died;
	pthread_mutex_unlock(&rules->mutex[DEATH]);
	return dead;
}

long long get_time(void)
{
	struct timeval	timev;

	gettimeofday(&timev, NULL);
	return ((timev.tv_sec * 1000LL) + (timev.tv_usec / 1000));
}

void mark_as_dead(t_rules *rules)
{
	pthread_mutex_lock(&rules->mutex[DEATH]);
	rules->philo_died = true;
	pthread_mutex_unlock(&rules->mutex[DEATH]);
}

void	print_philo_action(t_philo *philo, char *action)
{
	if (!check_dead_flag(philo->rules))
	{
		pthread_mutex_lock(&philo->rules->mutex[PRINT]);
		printf("%lld %ld %s\n",get_time() - philo->rules->start_time, philo->id, action);
		pthread_mutex_unlock(&philo->rules->mutex[PRINT]);
	}
}

void	ph_sleep(long long time_ms, t_rules *rules)
{
	long long	start;

	start = get_time();
	while (!check_dead_flag(rules))
	{
		if (get_time() - start >= time_ms)
			break ;
		usleep(500);
	}
}
