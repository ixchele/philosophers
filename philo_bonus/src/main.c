/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:07:02 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/04 16:38:50 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

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
	if (data.num_of_meals == 0)
		return (0);
	if (init_data(&data) == -1)
		exit_when_error("Failed to initialize data\n");
	prepare_simulation(&data);
	clean_up(&data, 0, 1);
	return (0);
}
