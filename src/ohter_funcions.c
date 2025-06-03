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

bool	check_fullness_flag(t_rules *rules)
{
	bool	full;

	pthread_mutex_lock(&rules->mutex[FULLNESS]);
	full = rules->philo_full;
	pthread_mutex_unlock(&rules->mutex[FULLNESS]);
	return (full);
}

bool	simulation_end(t_rules *rules)
{
	return (check_death_flag(rules) || check_fullness_flag(rules));
}

bool	check_death_flag(t_rules *rules)
{
	bool dead;

	pthread_mutex_lock(&rules->mutex[DEATH]);
	dead = rules->philo_died;
	pthread_mutex_unlock(&rules->mutex[DEATH]);
	return (dead);
}

long long get_time(void)
{
	struct timeval	timev;

	gettimeofday(&timev, NULL);
	return ((timev.tv_sec * 1000LL) + (timev.tv_usec / 1000));
}

void	mark_as_full(t_rules *rules)
{
	pthread_mutex_lock(&rules->mutex[FULLNESS]);
	rules->philo_full = true;
	pthread_mutex_unlock(&rules->mutex[FULLNESS]);
}

void	mark_as_dead(t_rules *rules)
{
	pthread_mutex_lock(&rules->mutex[DEATH]);
	rules->philo_died = true;
	pthread_mutex_unlock(&rules->mutex[DEATH]);
}

void	print_philo_action(t_philo *philo, char *action)
{
	// bool	died;

	pthread_mutex_lock(&philo->rules->mutex[DEATH]);
	// died = philo->rules->philo_died;
	if (!philo->rules->philo_died)
		printf("%lld %ld %s\n",get_time() - philo->rules->start_time, philo->id, action);
	pthread_mutex_unlock(&philo->rules->mutex[DEATH]);
}

void	ph_sleep(long long time_u, t_rules *rules)
{
	long long	start;
	long long	now;

	start = get_time() * 1000;
	while (!simulation_end(rules))
	{
		now = get_time() * 1000;
		if (now - start >= time_u)
			break ;
		if (time_u - (now - start) > 1000)
			usleep(500);
		else
			usleep(100);
	}
}
