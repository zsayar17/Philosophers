/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozsayar <aozsayar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:47:27 by aozsayar          #+#    #+#             */
/*   Updated: 2023/01/26 22:47:27 by aozsayar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *ptr)
{
	int	number;
	int	sign;

	number = 0;
	sign = 1;
	if (ptr && *ptr == '-' && *(ptr++))
		sign -= 2;
	while (ptr && *ptr && (*ptr >= '0' && *ptr <= '9'))
		number = (number * 10) + (*(ptr++) - 48);
	if (!ptr || *ptr)
		return (-1);
	return (number * sign);
}

size_t	ft_strlen(char *ptr)
{
	size_t	count;

	count = 0;
	while (ptr && *(ptr++))
		count++;
	return (count);
}

size_t	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec * 0.001));
}

void	my_sleep(size_t time)
{
	size_t	now;

	now = get_current_time();
	while (get_current_time() - now < time)
		usleep(1000);
}

int	raise_error(char *error_msg)
{
	write(2, error_msg, ft_strlen(error_msg));
	return (EXIT_FAILURE);
}
