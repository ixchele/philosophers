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
# include <stdio.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define PRINT 0
# define DEATH 1
# define FULLNESS 2

typedef struct s_philo
{
	pthread_t		thread_id;
	long			id;
	long			meals_eaten;
	long long		last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	last_meal_mutex;
	bool			can_eat;
	pthread_mutex_t can_eat_mutex;
	pthread_mutex_t	meal_eat_mut;
	struct s_rules	*rules;
}	t_philo;

typedef struct s_middleman
{
	pthread_mutex_t	**forks;
	bool			*taken;
	pthread_mutex_t	taken_mut;
}	t_middleman;

typedef struct s_rules
{
	long			nb_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			max_meal;
	bool			philo_died;
	bool			philo_full;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*mutex;
	t_philo			*philos;
	t_middleman		*middleman;
}	t_rules;

long		ph_atol(const char *nptr);
bool		check_death_flag(t_rules *rules);
bool		simulation_end(t_rules *rules);
long long	get_time(void);
void		mark_as_dead(t_rules *rules);
void		mark_as_full(t_rules *rules);
void		print_philo_action(t_philo *philo, char *action);
void		ph_sleep(long long time_ms, t_rules *rules);
bool		parse_args(t_rules *rules, int ac, char **av);
bool		init_all(t_rules *rules);
void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);
void		*philo_loop(void *arg);
void		start_the_dining(t_rules *rules);

#endif
