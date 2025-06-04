/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:10:29 by zbengued          #+#    #+#             */
/*   Updated: 2025/06/03 16:33:06 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

long	ph_atol(const char *nptr)
{
	long	n;
	long	prev;

	n = 0;
	if (!nptr || !nptr[0])
		return (-1);
	while (*nptr && ft_isdigit(*nptr))
	{
		prev = n;
		n = (*(nptr++) - '0') + n * 10;
		if (n < prev)
			return (-1);
	}
	if (*nptr && !ft_isdigit(*nptr))
		return (-1);
	return (n);
}

void	mark_as_dead(t_rules *rules)
{
	pthread_mutex_lock(&rules->mutex[DEATH]);
	rules->philo_died = true;
	pthread_mutex_unlock(&rules->mutex[DEATH]);
}

void	print_philo_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->rules->mutex[DEATH]);
	if (!philo->rules->philo_died)
		printf("%s%lld%s %ld %s\n", COLOR_RED,
			get_time() - philo->rules->start_time,
			COLOR_RESET, philo->id, action);
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
