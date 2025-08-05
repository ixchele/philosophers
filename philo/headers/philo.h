/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:44:34 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/04 16:53:34 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <colors.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIE 5

typedef pthread_mutex_t		t_mtx;
typedef struct s_program	t_program;

typedef struct s_philo
{
	pthread_t	thread_id;
	int		 	id;
	long	 	meals_eaten;
	long	 	last_eating_time;
	bool	 	is_full;
	t_mtx	 	philo_mtx;
	t_mtx	 	check_threads_mutex;
	t_mtx	 	*first_fork;
	t_mtx	 	*second_fork;
	t_program	*program;
}	t_philo;

struct s_program
{
	pthread_t	admin_thread;
	bool	 	threads_ready;
	bool	 	end_of_program;
	long	 	all_full;
	long	 	philo_nbr;
	long	 	start_dinner;
	long	 	time_to_eat;
	long	 	time_to_sleep;
	long	 	time_to_die;
	long	 	num_of_meals;
	t_mtx	 	data_mutex;
	t_mtx	 	write_mutex;
	t_mtx	 	*forks;
	t_philo	 	*philos;
};

bool	parse_args(t_program *rules, int ac, char **av);

void	give_forks(t_philo *philo, t_mtx *forks, int philo_position);
void	init_data(t_program *data);

void	*start_simulation(void *params);
void	prepare_simulation(t_program *data);

void	*middle_man_routine(void *param);

long	read_long(t_mtx *data_mutex, long *value);
bool	read_bool(t_mtx *data_mutex, bool *value);
void	set_long(t_mtx *data_mutex, long *variable, long new_val);
void	set_bool(t_mtx *data_mutex, bool *variable, bool new_val);
bool	end_of_simulation(t_program *data);

void	think_action(t_philo *philo);
void	eat_action(t_philo *philo);
void	sleep_action(t_philo *philo);

long	ph_atol(const char *nptr);
int		ft_strcmp(char *s1, char *s2);
void	exit_when_error(char *str);
void	increment(t_mtx *data_mutex, long *variable);

long	get_current_time(void);
int		ft_usleep(long time);
void	print_status(t_philo *philo, int state);
bool	all_philos_full(t_program *data);
void	clean_exit(t_program *data);

#endif // !PHILO_H  	
