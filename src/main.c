/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:58:33 by zbengued          #+#    #+#             */
/*   Updated: 2025/05/21 18:29:05 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

// TODO : 
// [x] parse_args()
// [] init_all()
// [] start_simulation()
// [] destroy_all()
//

bool	parse_args(t_rules *rules, int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (false);
	rules->max_meal = -2;
	rules->number_of_philosophers = ph_atol(av[1]);
	rules->time_to_die = ph_atol(av[2]);
	rules->time_to_eat = ph_atol(av[3]);
	rules->time_to_sleep = ph_atol(av[4]);
	if (ac == 6)
		rules->max_meal = ph_atol(av[5]);
	if (rules->max_meal == -1 || rules->number_of_philosophers == -1
			|| rules->time_to_die == -1 || rules->time_to_eat == -1
			|| rules->time_to_sleep == -1)
		return (false);
	return (true);
}

int main (int ac, char **av)
{
	t_rules rules;

	if (ac != 5 && ac != 6)
		return (-1);
	if (!parse_args(&rules, ac, av))
		return (printf("parse error\n"),-1);
	printf("number_of_philosophers ; %ld\n", ph_atol(av[1]));
	printf("time_to_die ; %ld\n", ph_atol(av[2]));
	printf("time_to_eat ; %ld\n", ph_atol(av[3]));
	printf("time_to_sleep ; %ld\n", ph_atol(av[4]));
	if (ac == 6)
		printf("number_of_times_each_philosopher_must_eat ; %ld\n", ph_atol(av[5]));
}
