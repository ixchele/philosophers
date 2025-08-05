/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:01:34 by olaaroub          #+#    #+#             */
/*   Updated: 2025/08/04 16:43:21 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <colors.h>

# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIE 5

typedef struct s_program	t_program;

typedef struct s_named_semaphores
{
	sem_t	*sem;
	char 	*name;
}	t_named_semaphores;

typedef struct s_wait
{
	sem_t	*stop;
	sem_t	*died;
	int	 	*pids;
	long 	pids_num;
	bool 	stop_flag;
}	t_wait;

typedef struct s_philo
{
	pthread_t			thread;
	t_named_semaphores	*local_sem;
	t_named_semaphores	*meal_sem;
	t_named_semaphores	*value_sem;
	bool				is_full;
	int					id;
	long				meals_eaten;
	long				last_eating_time;
	t_program			*program;
}	t_philo;

struct	s_program
{
	long				philo_nbr;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				num_of_meals;
	long				start_dinner;
	t_named_semaphores	*die_sem;
	t_named_semaphores	*global_sem;
	t_named_semaphores	*forks_sem;
	t_named_semaphores	*end_prog_sem;
	bool				end_of_program;
	int					*pids;
	t_philo				philos;
};

// NOTE : parse_and_init : 
bool	parse_args(t_program *rules, int ac, char **av);

int		ft_sem_open(t_named_semaphores **sem, char *namee, int id);
int		init_data(t_program *data);

// NOTE : run_simulation :
void	prepare_simulation(t_program *data);

void	*admin_routine(void *param);

// NOTE : utils : 
long	read_long(sem_t *sem, long *value);
bool	read_bool(sem_t *sem, bool *value);
void	set_long(sem_t *sem, long *variable, long new_val);
void	set_bool(sem_t *sem, bool *variable, bool new_val);
long	check_death(sem_t *from, sem_t *lock);

char	*ft_itoa(int n);
char	*ft_strdup(char *s1);
char	*ft_strdup(char *s1);
int		ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);

void	eat_action(t_philo *philo);
void	sleep_action(t_philo *philo);
void	think_action(t_philo *philo);

long	ft_atol(const char *nptr);
int		ft_strcmp(char *s1, char *s2);
int		ft_isdigit(int c);
int		is_space(int c);

int		ft_usleep(long time);
void	print_status(t_philo *philo, int state);
void	clean_up(t_program *data, unsigned int exit_num, bool mode);
long	get_current_time(void);

int		open_sems(t_philo *philo);
bool	end_of_dinner(t_program *data);
void	exit_when_error(char *str);

#endif
