/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:48:01 by zbengued          #+#    #+#             */
/*   Updated: 2025/05/21 18:23:59 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>

# define PRINT 0
# define DEATH 1

typedef struct s_philo
{
	pthread_t		thread_id;
	long			id;
	long			meals_eaten;
	long long		last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	last_meal_mutex;
	struct s_rules	*rules;
}	t_philo;

typedef struct s_rules
{
	long			nb_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			max_meal;
	bool			philo_died;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*death_mutex;
	t_philo			*philos;
}	t_rules;

int		ph_atoi(const char *str);
long	ph_atol(const char *nptr);

bool	parse_args(t_rules *rules, int ac, char **av);
bool	init_all(t_rules *rules);

#endif
