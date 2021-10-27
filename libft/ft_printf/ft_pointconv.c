/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointconv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarsenio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 04:21:39 by jarsenio          #+#    #+#             */
/*   Updated: 2021/04/22 04:21:41 by jarsenio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	empty_ptr_neg(t_flags s_fl)
{
	int	counter;

	counter = 0;
	if (s_fl.dot == 0)
	{
		counter += putstr_w_prec("0x", 2);
		counter += print_width(s_fl.width, 0, 2);
	}
	else
	{
		counter += putstr_w_prec("0x0", 3);
		counter += print_width(s_fl.width, 0, 3);
	}
	return (counter);
}

int	empty_ptr(t_flags s_fl)
{
	int	counter;

	counter = 0;
	if (s_fl.minus == 1)
		counter += empty_ptr_neg(s_fl);
	else
	{
		if (s_fl.dot == 0)
		{
			counter += print_width(s_fl.width, 0, 2);
			counter += putstr_w_prec("0x", 2);
		}
		else
		{
			counter += print_width(s_fl.width, 0, 3);
			counter += putstr_w_prec("0x0", 3);
		}
	}
	return (counter);
}

int	ptr_width(char *str, t_flags s_fl)
{
	int	counter;

	counter = 0;
	if (s_fl.dot >= 0)
	{
		counter += putstr_w_prec("0x", 2);
		counter += print_width(s_fl.dot, 1, ft_strlenpf(str));
		counter += putstr_w_prec(str, s_fl.dot);
	}
	else
	{
		counter += putstr_w_prec("0x", 2);
		counter += putstr_w_prec(str, ft_strlenpf(str) + 2);
	}
	return (counter);
}

int	pointer_conv(unsigned long long ptr, t_flags s_fl)
{
	int		counter;
	char	*str;

	counter = 0;
	if (ptr == 0 && (s_fl.dot == 0 || s_fl.dot == -1))
		return (empty_ptr(s_fl));
	str = unsigneditoa(ptr, 16);
	str = ft_tolowerpf(str);
	if (s_fl.dot < ft_strlenpf(str))
		s_fl.dot = ft_strlenpf(str);
	if (s_fl.minus == 1)
		counter += ptr_width(str, s_fl);
	if (s_fl.width > s_fl.dot)
		counter += print_width(s_fl.width, 0, s_fl.dot + 2);
	if (s_fl.minus == 0)
		counter += ptr_width(str, s_fl);
	free(str);
	return (counter);
}
