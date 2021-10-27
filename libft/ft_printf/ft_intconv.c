/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intconv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarsenio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:21:08 by jarsenio          #+#    #+#             */
/*   Updated: 2021/04/21 14:21:11 by jarsenio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	callfunc(t_flags s_fl, int sign, char *str, int num)
{
	int	counter;

	counter = 0;
	if (num < 0 && sign == 0 && s_fl.zero == 0)
	{
		sign = 2;
		s_fl.width--;
	}
	if (s_fl.dot >= 0 && (s_fl.dot < ft_strlenpf(str)))
		s_fl.dot = ft_strlenpf(str);
	if (s_fl.minus == 1)
		counter += print_int(num, &sign, str, s_fl);
	counter += intwidth(s_fl, sign, num, str);
	if (s_fl.minus == 0)
		counter += print_int(num, &sign, str, s_fl);
	return (counter);
}

int	intwidth(t_flags s_fl, int sign, int num, char *str)
{
	int	counter;

	counter = 0;
	if (s_fl.dot >= 0 && (s_fl.width > s_fl.dot))
		counter += print_width(s_fl.width, 0, s_fl.dot);
	else if (s_fl.dot >= 0 && (s_fl.dot > ft_strlenpf(str)))
		counter += print_width(s_fl.width, 0, s_fl.dot);
	else if (num < 0 && s_fl.zero == 1 && sign == 1)
		counter += print_width(s_fl.width, 1, ft_strlenpf(str) + 1);
	else if (num < 0)
		counter += print_width(s_fl.width, 0, ft_strlenpf(str));
	else
		counter += print_width(s_fl.width, s_fl.zero, ft_strlenpf(str));
	return (counter);
}

int	print_int(int num, int *sign, char *str, t_flags s_fl)
{
	int	counter;

	counter = 0;
	if (num < 0 && *sign == 2)
	{
		counter += ft_putchar('-');
		*sign = 1;
	}
	if (s_fl.dot >= 0)
		counter += print_width(s_fl.dot, 1, ft_strlenpf(str));
	if (s_fl.dot <= -1)
		s_fl.dot = ft_strlenpf(str);
	counter += putstr_w_prec(str, s_fl.dot);
	return (counter);
}

int	zero(t_flags s_fl)
{
	int	counter;

	counter = 0;
	if (s_fl.width == 0 && s_fl.dot <= -1)
		counter += ft_putchar('0');
	else if (s_fl.minus == 1)
		counter += zero_neg(s_fl);
	else
		counter += zero_posi(s_fl);
	return (counter);
}

int	conv_int(int num, t_flags s_fl)
{
	int		counter;
	char	*str;
	int		sign;

	counter = 0;
	sign = 0;
	if (s_fl.zero == 1 && s_fl.dot >= 0)
		s_fl.zero = 0;
	if (num == 0)
	{
		counter += zero(s_fl);
		return (counter);
	}
	if (num < 0 && s_fl.zero == 1 && s_fl.dot <= -1)
	{
		counter += putstr_w_prec("-", 1);
		sign = 1;
	}
	str = ft_itoapf(num * -1);
	counter += callfunc(s_fl, sign, str, num);
	free(str);
	return (counter);
}
