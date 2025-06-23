/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:39:57 by mogawa            #+#    #+#             */
/*   Updated: 2023/07/20 13:59:12 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/time.h>
# include <signal.h>
# include <sys/wait.h>
# include <limits.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>

# define DEATH 1
# define MAXLOOP 0

typedef struct s_table
{
	char		*sem_fork_name;
	sem_t		*sem_fork_id;
	char		*sem_print_name;
	sem_t		*sem_print_id;
	int			n_philos;
	int			time_die;
	int			time_eat;
	int			time_slp;
	int			max_eat;
	long long	start_ms;
}				t_table;

//*** libft ***
int			ft_isdigit(int c);
int			ft_isdigit_hex(int c, int base);
int			ft_isspace(const char c);
int			ft_atoi(const char *str);
long		ft_strtol(const char *str, char **endptr, int base_num);
void		*ft_calloc(size_t count, size_t size);
//*** init.c ***
int			init_handler(t_table *tbl, int argc, char **argv);
//*** utils ***
long long	get_cur_ms(void);
void		ft_xprintf(char *str, int idx, t_table *tbl);
void		ft_xusleep(int microsec);
int			ft_xatoi(const char *str, bool *to_exit, int n_av);
//***process
void		proc_handler(t_table *tbl);
void		child_proc(t_table *tbl, int i);
void		parent_proc(pid_t *pid_arr, t_table *tbl);

#endif
// INT＝43億ミリセカンド＝4294967秒＝1193時間