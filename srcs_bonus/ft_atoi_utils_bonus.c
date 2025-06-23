/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 06:38:04 by mogawa            #+#    #+#             */
/*   Updated: 2023/06/29 18:29:11 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 文字ｃが数値なら１を返し、それ以外は０を返す
int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	else
		return (0);
}

/*
*param	文字C
*return	１から９なら２、a-f & A-Fなら1、それ以外は０
*/
int	ft_isdigit_hex(int c, int base)
{
	if (ft_isdigit(c))
		return (-1);
	else if (base == 16 && 'A' <= c && c <= 'F')
		return (1);
	else if (base == 16 && 'a' <= c && c <= 'f')
		return (1);
	else
		return (0);
}

int	ft_isspace(const char c)
{
	if (c == ' ' || c == '\f' || c == '\n' || c == '\r'
		|| c == '\t' || c == '\v')
		return (1);
	else
		return (0);
}
