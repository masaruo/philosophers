/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:46:24 by mogawa            #+#    #+#             */
/*   Updated: 2023/07/20 14:06:47 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_table	tbl;

	if (argc != 5 && argc != 6)
	{
		printf("wrong number of arguments provided.\n");
		return (EXIT_FAILURE);
	}
	if (init_handler(&tbl, argc, argv) == EXIT_FAILURE)
	{
		printf("initialization of philosophers failed.\n");
		printf("number of philosophers must be 0 < n <= 200.\n");
		printf("time to eat and time to sleep must be 0 < n < 1000ms.\n");
		return (EXIT_FAILURE);
	}
	proc_handler(&tbl);
	return (EXIT_SUCCESS);
}
