/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:16:40 by mogawa            #+#    #+#             */
/*   Updated: 2023/07/18 15:08:22 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
引数| VOID型の文字列:*s＆バイト数:size_st n
戻り値| なし
フリー| 不要
機能| 文字列ｓにｎバイト分の０を書き込む
*/
static void	ft_bzero_philo(void *s, size_t n)
{
	memset(s, 0, n);
}

/*
引数| カウント:count＆カウントあたりのサイズ:size_t size
戻り値| メモリー領域へのポインタ
フリー| 必要
機能| 0埋めしたメモリーを'size' x 'count'分確保
*/
void	*ft_calloc(size_t count, size_t size)
{
	void	*heap;
	size_t	amount;

	if (count == 0 || size == 0)
		return (NULL);
	if (SIZE_MAX / size < count)
		return (NULL);
	amount = count * size;
	heap = malloc(amount);
	if (heap == NULL)
		return (NULL);
	ft_bzero_philo(heap, amount);
	return (heap);
}
