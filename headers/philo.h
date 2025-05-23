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

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H


#include <bits/pthreadtypes.h>
# include <stdbool.h>
# include <pthread.h>
# include <stdio.h>


typedef struct	s_rules
{
	long			number_of_philosophers;
	long			time_to_die;
    long			time_to_eat;
	long			time_to_sleep;
	long			max_meal;
	pthread_mutex_t	*forks;

}	t_rules;

typedef struct	s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_rules			*rules;
}	t_philo;

int		ph_atoi(const char *str);
long	ph_atol(const char *nptr);

#endif

