/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:13:19 by mogawa            #+#    #+#             */
/*   Updated: 2023/07/18 06:45:54 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	death_handler(t_table *tbl, int i)
{
	pthread_mutex_lock(&tbl->stop_lock);
	if (tbl->to_stop != FINISHED)
	{
		pthread_mutex_unlock(&tbl->stop_lock);
		ft_xprintf(tbl->philos[i].idx, "died", tbl);
		pthread_mutex_lock(&tbl->stop_lock);
		tbl->to_stop = DEATH;
		pthread_mutex_unlock(&tbl->stop_lock);
	}
	pthread_mutex_unlock(&tbl->stop_lock);
}

void	thread_monitor(t_table *tbl)
{
	int	i;

	while (1)
	{
		i = 0;
		ft_xusleep(tbl->time_die + 1);
		while (i < tbl->n_philos)
		{
			pthread_mutex_lock(&tbl->waiter);
			if ((int)(get_cur_ms() - tbl->start_ms) \
						- tbl->philos[i].last_eat >= tbl->time_die)
			{
				pthread_mutex_unlock(&tbl->waiter);
				death_handler(tbl, i);
				return ;
			}
			pthread_mutex_unlock(&tbl->waiter);
			i++;
		}
	}
}
