/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozsayar <aozsayar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:46:46 by aozsayar          #+#    #+#             */
/*   Updated: 2023/01/26 22:46:46 by aozsayar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_loop(t_core *core)
{
	t_philos	*philos;

	philos = core->philos;
	while (philos)
	{
		philos->last_eat_time = get_current_time();
		philos->begin_time = philos->last_eat_time;
		pthread_create(&philos->thread_id, NULL, &loop, (void *)philos);
		philos = philos->next;
	}
	check_die((void *)core);
	philos = core->philos;
	while (philos)
	{
		pthread_join(philos->thread_id, NULL);
		philos = philos->next;
	}
}

void	*loop(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	if (philo->core->philo_nbr == 1)
		return (NULL);
	if (philo->philo_id % 2)
		my_sleep(philo->core->time_to_eat * 0.5);
	while (1)
	{
		if (circle(philo))
			break ;
	}
	return (NULL);
}
