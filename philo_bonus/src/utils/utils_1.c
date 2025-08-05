/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils-v1_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:08:10 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/04 16:19:32 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

long	ft_atol(const char *nptr)
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

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	is_space(int c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

long	get_current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (printf("gettimeofday() error \n"), -1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
