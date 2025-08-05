/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:06:31 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/04 16:17:11 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

bool	parse_args(t_program *rules, int ac, char **av)
{
	long	*fields;
	int		i;

	if (ac != 5 && ac != 6)
		return (false);
	fields = (long *)rules;
	i = 0;
	if (ac != 5 && ac != 6)
		return (false);
	rules->num_of_meals = -2;
	rules->philo_nbr = ft_atol(av[1]);
	rules->time_to_die = ft_atol(av[2]);
	rules->time_to_eat = ft_atol(av[3]);
	rules->time_to_sleep = ft_atol(av[4]);
	if (ac == 6)
		rules->num_of_meals = ft_atol(av[5]);
	while (i < 5)
	{
		if (fields[i] == -1)
			return (false);
		i++;
	}
	return (true);
}
