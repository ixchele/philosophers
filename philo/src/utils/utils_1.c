/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:43:52 by zbengued          #+#    #+#             */
/*   Updated: 2025/06/03 15:44:09 by zbengued         ###   ########.fr       */
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
	bool	dead;

	pthread_mutex_lock(&rules->mutex[DEATH]);
	dead = rules->philo_died;
	pthread_mutex_unlock(&rules->mutex[DEATH]);
	return (dead);
}

long long	get_time(void)
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
