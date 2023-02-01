/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozsayar <aozsayar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:47:24 by aozsayar          #+#    #+#             */
/*   Updated: 2023/01/26 22:47:24 by aozsayar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

# define ALIVE 0
# define DEATH 1
# define RESET "\e[0m"
# define RED "\e[0;38;5;199m"
# define GREEN "\e[0;32m"
# define BLUE "\e[0;34m"
# define YELLOW "\e[0;33m"
# define CYAN "\e[0;36m"
# define G_CYAN "\e[0;38;5;44m"
# define DEATH_MSG "dead"
# define FORK_MSG "has taken all forks"
# define SLEEP_MSG "is sleeping"
# define THINK_MSG "is thinking"
# define EAT_MSG "is eating"

typedef struct s_core
{
	int				philo_nbr;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	size_t			status;
	size_t			full_philos;
	pthread_mutex_t	*mutexes;
	pthread_mutex_t	*pr_mtx;
	pthread_mutex_t	*ch_mtx;
	pthread_mutex_t	*dt_mtx;
	struct s_philos	*philos;
}	t_core;

typedef struct s_philos
{
	pthread_t		thread_id;
	int				philo_id;
	pthread_mutex_t	*r_chopstick;
	pthread_mutex_t	*l_chopstick;
	int				eat_count;
	size_t			begin_time;
	size_t			last_eat_time;
	size_t			current_time;
	struct s_core	*core;
	struct s_philos	*next;
}	t_philos;

int		fill_core(t_core *core, int argc, char **argv);
void	create_philos(t_core *core);
void	create_mutexes(t_core *core);
void	create_new_philo(t_core *core);
void	clear_loop(t_core *core);

void	start_loop(t_core *core);
void	*loop(void *arg);

void	*check_die(void *arg);
int		circle(t_philos *philo);
int		rd_value(pthread_mutex_t *mutex, size_t *value);
void	wr_value(pthread_mutex_t *mutex, size_t *value, size_t new_value);
int		print_msg(t_philos *philo, char *msg, char *color, int e_wr);

void	my_sleep(size_t time);
int		ft_atoi(char *ptr);
size_t	ft_strlen(char *ptr);
size_t	get_current_time(void);
int		raise_error(char *error_msg);

#endif
