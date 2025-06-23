/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:06:45 by mogawa            #+#    #+#             */
/*   Updated: 2023/07/17 20:05:13 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_init(t_table *tbl, pthread_mutex_t *forks, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < tbl->n_philos)
	{
		philos[i].idx = i;
		if (i == 0)
			philos[i].fork_r = &forks[tbl->n_philos - 1];
		else
			philos[i].fork_r = &forks[i - 1];
		philos[i].fork_l = &forks[i];
		philos[i].tbl = tbl;
		philos[i].last_eat = (int) get_cur_ms() - tbl->start_ms;
		i++;
	}
	tbl->philos = philos;
}

int	mutex_initializer(t_table *tbl)
{
	int	i;

	if (pthread_mutex_init(&tbl->stop_lock, NULL))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&tbl->waiter, NULL))
	{
		pthread_mutex_destroy(&tbl->stop_lock);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (i < tbl->n_philos)
	{
		if (pthread_mutex_init(&(tbl->forks[i]), NULL))
		{
			pthread_mutex_destroy(&tbl->stop_lock);
			pthread_mutex_destroy(&tbl->waiter);
			while (i > 0)
			{
				pthread_mutex_destroy(&tbl->forks[--i]);
			}
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_philos(t_table *tbl)
{
	t_philo			*philos;
	pthread_mutex_t	*forks;

	philos = ft_calloc(tbl->n_philos, sizeof(t_philo));
	if (!philos)
		return (EXIT_FAILURE);
	forks = ft_calloc(tbl->n_philos, sizeof(pthread_mutex_t));
	if (!forks)
	{
		free (philos);
		return (EXIT_FAILURE);
	}
	tbl->forks = forks;
	if (mutex_initializer(tbl) == EXIT_FAILURE)
	{
		free (philos);
		free (forks);
		return (EXIT_FAILURE);
	}
	philo_init(tbl, forks, philos);
	return (EXIT_SUCCESS);
}

int	init_handler(t_table *tbl, int argc, char **argv)
{
	bool	to_exit;

	to_exit = false;
	tbl->n_philos = ft_xatoi(argv[1], &to_exit, 1);
	tbl->time_die = ft_xatoi(argv[2], &to_exit, 2);
	tbl->time_eat = ft_xatoi(argv[3], &to_exit, 3);
	tbl->time_slp = ft_xatoi(argv[4], &to_exit, 4);
	if (argc == 6)
		tbl->max_eat = ft_xatoi(argv[5], &to_exit, 5);
	else
		tbl->max_eat = INT_MAX;
	if (to_exit == true)
		return (EXIT_FAILURE);
	tbl->start_ms = get_cur_ms();
	tbl->to_stop = CONTINUE;
	if (init_philos(tbl) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
