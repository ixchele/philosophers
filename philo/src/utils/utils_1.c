/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 17:36:47 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/03 16:07:38 by zbengued         ###   ########.fr       */
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

int	ft_strcmp(char *s1, char *s2)
{
	while ((*s1 && *s2) && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (s1 - s2);
}

void	exit_when_error(char *str)
{
	printf("%s", str);
	exit(EXIT_FAILURE);
}

void	increment(t_mtx *data_mutex, long *variable)
{
	pthread_mutex_lock(data_mutex);
	*variable = *variable + 1;
	pthread_mutex_unlock(data_mutex);
}
