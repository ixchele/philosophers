/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:58:33 by zbengued          #+#    #+#             */
/*   Updated: 2025/05/28 15:13:21 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
// TODO : 
// [x] parse_args()
// [x] init_all()
// [] start_simulation()
// [] destroy_all()
// -----------------

static void	print_usage(void)
{
	printf("Usage ; ./philo [number_of_philosophers] ");
	printf("[time_to_die] [time_to_eat] [time_to_sleep] ");
	printf("(optional argument ");
	printf("[number_of_times_each_philosopher_must_eat])\n");
}

int	main(int ac, char **av)
{
	t_rules	rules;

	if (ac != 5 && ac != 6)
		return (print_usage(), -1);
	if (!parse_args(&rules, ac, av))
		return (printf("parse error\n"), -1);
	if (!init_all(&rules))
		return (printf("error in initialisation"), -1);
	start_the_dining(&rules);
}
