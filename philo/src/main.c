/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:09:19 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/03 16:23:52 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
// TODO : 
// [x] parse_args()
// [x] init_all()
// [x] start_simulation()
// [x] destroy_all()
// -----------------

static void	print_usage(void)
{
	printf(COLOR_RED"ERROR!\nUsage ;\n"COLOR_BLUE
		"[number_of_philosophers : size_t]\n"
		"[time_to_die : unsinged long]\n"
		"[time_to_eat : unsinged long]\n"
		"[time_to_sleep : unsinged long]\n"
		COLOR_YELLOW"(optional)"COLOR_BLUE
		"[number_of_times_each_philosopher_must_eat : size_t]\n");
}

int	main(int ac, char **av)
{
	t_program	data;

	if (!parse_args(&data, ac, av))
		return (print_usage(), -1);
	init_data(&data);
	prepare_simulation(&data);
	clean_exit(&data);
	return (0);
}
