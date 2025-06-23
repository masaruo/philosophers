/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:36:05 by mogawa            #+#    #+#             */
/*   Updated: 2023/07/20 14:08:05 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	one_philo(t_table *tbl, int i)
{
	ft_xprintf("has taken a fork", i, tbl);
	ft_xusleep(tbl->time_die + 1);
	exit (DEATH);
}

/*
dprintf(2, "(%d):%lld - %lld = %lld vs %d\n", i, get_cur_ms(), 
last_eat, get_cur_ms() - last_eat, tbl->time_die);
*/
void	child_proc(t_table *tbl, int i)
{
	int			n;
	long long	last_eat;

	last_eat = tbl->start_ms;
	n = 0;
	while (1)
	{
		if (tbl->n_philos == 1)
			one_philo(tbl, i);
		if (n > tbl->max_eat && tbl->max_eat > 0)
			exit(MAXLOOP);
		sem_wait(tbl->sem_fork_id);
		if (get_cur_ms() - last_eat >= tbl->time_die)
			exit(DEATH);
		ft_xprintf("has taken a fork", i, tbl);
		ft_xprintf("has taken a fork", i, tbl);
		ft_xprintf("is eating", i, tbl);
		last_eat = get_cur_ms();
		ft_xusleep(tbl->time_eat);
		sem_post(tbl->sem_fork_id);
		ft_xprintf("is sleeping", i, tbl);
		ft_xusleep(tbl->time_slp);
		ft_xprintf("is thinking", i, tbl);
		n++;
	}
}

void	parent_proc(pid_t *pid_arr, t_table *tbl)
{
	int		status;
	pid_t	exited_pid;
	int		j;

	sem_unlink(tbl->sem_fork_name);
	sem_unlink(tbl->sem_print_name);
	sem_close(tbl->sem_fork_id);
	sem_close(tbl->sem_print_id);
	exited_pid = waitpid(-1, &status, 0);
	j = 0;
	while (j < tbl->n_philos)
	{
		if (pid_arr[j] == exited_pid)
		{
			if (WEXITSTATUS(status) == DEATH)
				ft_xprintf("died", j, tbl);
			j++;
			continue ;
		}
		kill(pid_arr[j++], SIGTERM);
	}
	while (waitpid(0, NULL, WNOHANG) > 0)
		continue ;
	free(pid_arr);
	exit(EXIT_SUCCESS);
}

pid_t	*init_sem_and_heap(t_table *tbl)
{
	pid_t	*pid_arr;

	tbl->sem_fork_id = sem_open(tbl->sem_fork_name, O_CREAT | O_EXCL, \
												0777, tbl->n_philos / 2);
	tbl->sem_print_id = sem_open(tbl->sem_print_name, O_CREAT | O_EXCL, \
												0777, 1);
	if (tbl->sem_fork_id == SEM_FAILED || tbl->sem_print_id == SEM_FAILED)
		exit (EXIT_FAILURE);
	pid_arr = ft_calloc(tbl->n_philos, sizeof(pid_t));
	if (!pid_arr)
		exit (EXIT_FAILURE);
	return (pid_arr);
}

void	proc_handler(t_table *tbl)
{
	int		i;
	pid_t	pid;
	pid_t	*pid_arr;

	pid_arr = init_sem_and_heap(tbl);
	tbl->start_ms = get_cur_ms();
	i = 0;
	while (i < tbl->n_philos)
	{
		pid = fork();
		if (pid < 0)
		{
			free (pid_arr);
			exit (EXIT_FAILURE);
		}
		else if (pid == 0)
			break ;
		else
			pid_arr[i] = pid;
		i++;
	}
	if (pid != 0)
		parent_proc(pid_arr, tbl);
	else
		child_proc(tbl, i);
}
