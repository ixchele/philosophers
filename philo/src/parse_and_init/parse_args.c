/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 11:19:59 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/03 16:48:08 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

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
	rules->philo_nbr = ph_atol(av[1]);
	rules->time_to_die = ph_atol(av[2]);
	rules->time_to_eat = ph_atol(av[3]);
	rules->time_to_sleep = ph_atol(av[4]);
	if (ac == 6)
		rules->num_of_meals = ph_atol(av[5]);
	while (i < 5)
	{
		if (fields[i] == -1)
			return (false);
		i++;
	}
	return (true);
}
