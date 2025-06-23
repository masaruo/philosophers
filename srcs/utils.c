/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:10:01 by mogawa            #+#    #+#             */
/*   Updated: 2023/07/17 19:39:25 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_cur_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_xprintf(int idx, char *str, t_table *tbl)
{
	int	now_ms;

	pthread_mutex_lock(&tbl->stop_lock);
	now_ms = get_cur_ms() - tbl->start_ms;
	if (tbl->to_stop != DEATH)
		printf("%d %d %s\n", now_ms, idx, str);
	pthread_mutex_unlock(&tbl->stop_lock);
}

void	ft_xusleep(int ms)
{
	long long	now;

	now = get_cur_ms();
	while (get_cur_ms() - now < ms)
		usleep(ms / 10);
}

int	ft_xatoi(const char *str, bool *to_exit, int n_av)
{
	int	tmp;

	tmp = ft_atoi(str);
	if (tmp <= 0)
		*to_exit = true;
	else if (n_av == 1 && tmp > 200)
		*to_exit = true;
	else if ((n_av == 3 || n_av == 4) && tmp > 1000)
		*to_exit = true;
	return (tmp);
}
