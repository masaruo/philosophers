/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:42:16 by mogawa            #+#    #+#             */
/*   Updated: 2023/07/18 06:47:09 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	to_continue(t_table *tbl)
{
	pthread_mutex_lock(&tbl->stop_lock);
	if (tbl->to_stop != CONTINUE)
	{
		pthread_mutex_unlock(&tbl->stop_lock);
		return (false);
	}
	else
	{
		pthread_mutex_unlock(&tbl->stop_lock);
		return (true);
	}
}

void	philo_eat(t_philo *philo, t_table *tbl)
{
	pthread_mutex_lock(philo->fork_r);
	ft_xprintf(philo->idx, "has taken a fork", tbl);
	if (tbl->n_philos == 1)
	{
		ft_xusleep(tbl->time_eat);
		return ;
	}
	pthread_mutex_lock(philo->fork_l);
	ft_xprintf(philo->idx, "has taken a fork", tbl);
	pthread_mutex_lock(&tbl->waiter);
	ft_xprintf(philo->idx, "is eating", tbl);
	philo->last_eat = get_cur_ms() - tbl->start_ms;
	pthread_mutex_unlock(&tbl->waiter);
	ft_xusleep(tbl->time_eat);
	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_unlock(philo->fork_l);
}

void	philo_sleep_and_think(t_philo *philo, t_table *tbl)
{
	ft_xprintf(philo->idx, "is sleeping", tbl);
	ft_xusleep(tbl->time_slp);
	ft_xprintf(philo->idx, "is thinking", tbl);
}

void	*philo_thread(void *arg)
{
	t_philo	*philo;
	t_table	*tbl;
	int		i;

	philo = (t_philo *) arg;
	tbl = philo->tbl;
	if (philo->idx % 2 != 0)
		ft_xusleep(tbl->time_eat / 10);
	i = 0;
	while (to_continue(tbl))
	{
		philo_eat(philo, tbl);
		if (tbl->n_philos == 1)
			return (NULL);
		if (i >= tbl->max_eat)
		{
			pthread_mutex_lock(&tbl->stop_lock);
			tbl->to_stop = FINISHED;
			pthread_mutex_unlock(&tbl->stop_lock);
			return (NULL);
		}
		philo_sleep_and_think(philo, tbl);
		i++;
	}
	return (NULL);
}

void	thread_handler(t_table *tbl)
{
	int		i;

	i = 0;
	while (i < tbl->n_philos)
	{
		pthread_create(&(tbl->philos[i].tid), NULL, \
					philo_thread, (void *)&tbl->philos[i]);
		i++;
	}
	thread_monitor(tbl);
}
