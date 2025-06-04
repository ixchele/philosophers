/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:58:33 by zbengued          #+#    #+#             */
/*   Updated: 2025/06/03 16:34:53 by zbengued         ###   ########.fr       */
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
	printf("%sUsage%s ; %s./philo [number_of_philosophers] ", COLOR_RED,
		COLOR_RED, COLOR_BLUE);
	printf("%s[time_to_die] [time_to_eat] [time_to_sleep] ", COLOR_BLUE);
	printf("%s(optional argument ", COLOR_GREEN);
	printf("[number_of_times_each_philosopher_must_eat])\n");
}

static void	destroy_all(t_rules *rules)
{
	long	i;

	i = 0;
	while (i < 3)
	{
		pthread_mutex_destroy(&rules->mutex[i]);
		i++;
	}
	i = 0;
	while (i < rules->nb_of_philos)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		pthread_mutex_destroy(&rules->philos[i].meal_eat_mut);
		pthread_mutex_destroy(&rules->philos[i].last_meal_mutex);
		i++;
	}
	free(rules->forks);
	free(rules->mutex);
	free(rules->philos);
}

int	main(int ac, char **av)
{
	t_rules	rules;

	if (ac != 5 && ac != 6)
		return (print_usage(), -1);
	if (!parse_args(&rules, ac, av))
		return (printf("%sparse error%s\n", COLOR_RED, COLOR_RESET), -1);
	if (!init_all(&rules))
		return (printf("error in initialisation\n"), -1);
	start_the_dining(&rules);
	destroy_all(&rules);
}
