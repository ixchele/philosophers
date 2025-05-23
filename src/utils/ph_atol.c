/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:31:59 by ihajji            #+#    #+#             */
/*   Updated: 2025/05/21 18:55:30 by zbengued         ###   ########.fr       */
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
