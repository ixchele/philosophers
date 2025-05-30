/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:12:01 by zbengued          #+#    #+#             */
/*   Updated: 2025/05/21 18:11:43 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	ph_atoi(const char *str)
{
	int	i;
	int	signe;
	int	x;

	i = 0;
	signe = 1;
	x = 0;
	while (str[i] == 32 || (str[i] <= 13 && str[i] >= 9))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		x = x * 10 + (str[i] - '0');
		i++;
	}
	return (x * signe);
}
