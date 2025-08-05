/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_write_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:07:58 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/04 16:18:06 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

long	read_long(sem_t *sem, long *value)
{
	long	res;

	sem_wait(sem);
	res = *value;
	sem_post(sem);
	return (res);
}

bool	read_bool(sem_t *sem, bool *value)
{
	bool	res;

	sem_wait(sem);
	res = *value;
	sem_post(sem);
	return (res);
}

void	set_long(sem_t *sem, long *variable, long new_val)
{
	sem_wait(sem);
	*variable = new_val;
	sem_post(sem);
}

void	set_bool(sem_t *sem, bool *variable, bool new_val)
{
	sem_wait(sem);
	*variable = new_val;
	sem_post(sem);
}

long	check_death(sem_t *from, sem_t *lock)
{
	long	res;

	res = 0;
	sem_wait(lock);
	res = from->__align;
	sem_post(lock);
	return (res);
}
