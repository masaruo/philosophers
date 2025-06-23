/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:39:35 by mogawa            #+#    #+#             */
/*   Updated: 2023/07/17 18:47:27 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_destroy_and_free(t_table *tbl)
{
	int	i;

	pthread_mutex_destroy(&tbl->stop_lock);
	pthread_mutex_destroy(&tbl->waiter);
	i = 0;
	while (i < tbl->n_philos)
	{
		pthread_mutex_destroy(&tbl->forks[i]);
		i++;
	}
	free(tbl->forks);
	free(tbl->philos);
}

void	threads_join(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->tbl->n_philos)
	{
		pthread_join(philos[i].tid, NULL);
		i++;
	}
}

void	final_handler(t_table *tbl)
{
	threads_join(tbl->philos);
	mutex_destroy_and_free(tbl);
}
