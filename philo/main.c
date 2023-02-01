/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozsayar <aozsayar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:46:59 by aozsayar          #+#    #+#             */
/*   Updated: 2023/01/26 22:46:59 by aozsayar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_core	core;

	if (fill_core(&core, argc, argv))
		return (1);
	start_loop(&core);
	clear_loop(&core);
}
