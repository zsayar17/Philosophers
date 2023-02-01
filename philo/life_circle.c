/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozsayar <aozsayar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:47:08 by aozsayar          #+#    #+#             */
/*   Updated: 2023/01/26 22:47:08 by aozsayar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_die(void *arg)
{
	t_core		*core;
	t_philos	*philo;
	size_t		current_time;

	core = (t_core *)arg;
	while (1)
	{
		philo = core->philos;
		while (philo)
		{
			if (rd_value(core->ch_mtx, &core->full_philos) == core->philo_nbr)
				return (NULL);
			pthread_mutex_lock(core->ch_mtx);
			current_time = get_current_time() - philo->last_eat_time;
			pthread_mutex_unlock(core->ch_mtx);
			if (current_time > (size_t)core->time_to_die)
			{
				wr_value(core->dt_mtx, &core->status, DEATH);
				print_msg(philo, DEATH_MSG, RED, 1);
				return (NULL);
			}
			philo = philo->next;
		}
	}
	return (NULL);
}

int	circle(t_philos *philo)
{
	pthread_mutex_lock(philo->r_chopstick);
	pthread_mutex_lock(philo->l_chopstick);
	print_msg(philo, FORK_MSG, BLUE, 0);
	print_msg(philo, EAT_MSG, GREEN, 0);
	my_sleep(philo->core->time_to_eat);
	pthread_mutex_unlock(philo->l_chopstick);
	pthread_mutex_unlock(philo->r_chopstick);
	wr_value(philo->core->ch_mtx, &philo->last_eat_time, get_current_time());
	philo->eat_count++;
	if (philo->eat_count == philo->core->must_eat)
	{
		pthread_mutex_lock(philo->core->ch_mtx);
		philo->core->full_philos++;
		pthread_mutex_unlock(philo->core->ch_mtx);
		return (1);
	}
	if (print_msg(philo, SLEEP_MSG, YELLOW, 0))
		return (1);
	my_sleep(philo->core->time_to_sleep);
	if (print_msg(philo, THINK_MSG, CYAN, 0))
		return (1);
	return (0);
}

int	rd_value(pthread_mutex_t *mutex, size_t *value)
{
	int	return_value;

	pthread_mutex_lock(mutex);
	return_value = *value;
	pthread_mutex_unlock(mutex);
	return (return_value);
}

void	wr_value(pthread_mutex_t *mutex, size_t *value, size_t new_value)
{
	pthread_mutex_lock(mutex);
	*value = new_value;
	pthread_mutex_unlock(mutex);
}

int	print_msg(t_philos *philo, char *msg, char *cl, int e_wr)
{
	pthread_mutex_lock(philo->core->pr_mtx);
	philo->current_time = get_current_time() - philo->begin_time;
	if (rd_value(philo->core->dt_mtx, &philo->core->status) == ALIVE || e_wr)
	{
		printf("%s%zu %d %s\n", cl, philo->current_time, philo->philo_id, msg);
		pthread_mutex_unlock(philo->core->pr_mtx);
		return (0);
	}
	pthread_mutex_unlock(philo->core->pr_mtx);
	return (1);
}
