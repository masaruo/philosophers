/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:39:57 by mogawa            #+#    #+#             */
/*   Updated: 2023/07/17 19:47:16 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/time.h>
# include <limits.h>

# define CONTINUE 0
# define DEATH 1
# define FINISHED 2

typedef struct s_philo
{
	pthread_t			tid;
	int					idx;
	int					last_eat;
	int					n_ate;
	struct s_table		*tbl;
	pthread_mutex_t		*fork_l;
	pthread_mutex_t		*fork_r;
}	t_philo;

typedef struct s_table
{
	int				n_philos;
	int				time_die;
	int				time_eat;
	int				time_slp;
	int				max_eat;
	long long		start_ms;
	pthread_mutex_t	stop_lock;
	int				to_stop;
	pthread_mutex_t	waiter;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_table;

//*** libft ***
int			ft_isdigit(int c);
int			ft_isdigit_hex(int c, int base);
int			ft_isspace(const char c);
int			ft_atoi(const char *str);
long		ft_strtol(const char *str, char **endptr, int base_num);
void		*ft_calloc(size_t count, size_t size);
//*** init.c ***
int			init_handler(t_table *tbl, int argc, char **argv);
//*** thread.c ***
void		thread_handler(t_table *tbl);
long long	get_cur_ms(void);
//*** monitor.c
void		thread_monitor(t_table *tbl);
//*** finalize.c ***
void		final_handler(t_table *tbl);
//*** utils ***
void		ft_xprintf(int idx, char *str, t_table *tbl);
void		ft_xusleep(int microsec);
int			ft_xatoi(const char *str, bool *to_exit, int n_av);

#endif
// INT＝43億ミリセカンド＝4294967秒＝1193時間