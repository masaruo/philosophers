/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:06:45 by mogawa            #+#    #+#             */
/*   Updated: 2023/07/20 13:58:03 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_handler(t_table *tbl, int argc, char **argv)
{
	bool	to_exit;

	to_exit = false;
	tbl->n_philos = ft_xatoi(argv[1], &to_exit, 1);
	tbl->time_die = ft_xatoi(argv[2], &to_exit, 2);
	tbl->time_eat = ft_xatoi(argv[3], &to_exit, 3);
	tbl->time_slp = ft_xatoi(argv[4], &to_exit, 4);
	tbl->sem_fork_name = "/sem_fork";
	tbl->sem_print_name = "/sem_print";
	if (argc == 6)
		tbl->max_eat = ft_xatoi(argv[5], &to_exit, 5);
	else
		tbl->max_eat = 0;
	if (to_exit == true)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}
