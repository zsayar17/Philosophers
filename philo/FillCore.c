/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FillCore.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozsayar <aozsayar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:47:15 by aozsayar          #+#    #+#             */
/*   Updated: 2023/01/26 22:47:15 by aozsayar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	fill_core(t_core *core, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (raise_error("Invalid argument count\n"));
	core->philo_nbr = ft_atoi(*(++argv));
	if (core->philo_nbr <= 0)
		return (raise_error("Invalid philo count\n"));
	core->time_to_die = ft_atoi(*(++argv));
	if (core->time_to_die <= 0)
		return (raise_error("Invalid time\n"));
	core->time_to_eat = ft_atoi(*(++argv));
	if (core->time_to_eat <= 0)
		return (raise_error("Invalid time\n"));
	core->time_to_sleep = ft_atoi(*(++argv));
	if (core->time_to_sleep <= 0)
		return (raise_error("Invalid time\n"));
	if (argc == 6)
		core->must_eat = ft_atoi(*(++argv));
	else
		core->must_eat = 0;
	if (core->must_eat < 0)
		return (raise_error("Invalid eat count\n"));
	core->status = ALIVE;
	core->full_philos = 0;
	create_mutexes(core);
	create_philos(core);
	return (0);
}

void	create_mutexes(t_core *core)
{
	int				index;
	int				count;
	pthread_mutex_t	*t_mutex;

	index = 0;
	count = core->philo_nbr;
	t_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (count + 3));
	core->mutexes = t_mutex;
	while (index++ <= count + 2)
		pthread_mutex_init(t_mutex++, NULL);
	core->pr_mtx = &core->mutexes[core->philo_nbr];
	core->ch_mtx = &core->mutexes[core->philo_nbr + 1];
	core->dt_mtx = &core->mutexes[core->philo_nbr + 2];
}

void	create_philos(t_core *core)
{
	int	index;

	core->philos = NULL;
	index = 0;
	while (index++ < core->philo_nbr)
		create_new_philo(core);
}

void	create_new_philo(t_core *core)
{
	t_philos	*temp_philo;
	t_philos	*new_philo;
	static int	philo_id;

	new_philo = (t_philos *)malloc(sizeof(t_philos));
	if (!core->philos)
		core->philos = new_philo;
	else
	{
		temp_philo = core->philos;
		while (temp_philo->next)
			temp_philo = temp_philo->next;
		temp_philo->next = new_philo;
	}
	new_philo->core = core;
	new_philo->philo_id = ++philo_id;
	new_philo->l_chopstick = &core->mutexes[philo_id - 1];
	new_philo->r_chopstick = &core->mutexes[philo_id % core->philo_nbr];
	new_philo->next = NULL;
	new_philo->eat_count = 0;
}

void	clear_loop(t_core *core)
{
	pthread_mutex_t	*t_mutex;
	int				index;
	t_philos		*t_philo;

	t_mutex = core->mutexes;
	index = 0;
	while (index++ <= core->philo_nbr + 2)
		pthread_mutex_destroy(t_mutex);
	free(core->mutexes);
	if (!core->philos)
		return ;
	while (core->philos)
	{
		t_philo = core->philos->next;
		free(core->philos);
		core->philos = t_philo;
	}
}
