/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charconv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarsenio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:20:55 by jarsenio          #+#    #+#             */
/*   Updated: 2021/04/21 14:20:58 by jarsenio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	conv_char(char c, t_flags s_fl)
{
	int	counter;

	counter = 0;
	if (s_fl.width > 1 && s_fl.zero == 1)
	{
		counter += print_width(s_fl.width, 1, 1);
		counter += ft_putchar(c);
		return (counter);
	}
	if (s_fl.minus == 1)
		counter += ft_putchar(c);
	counter += print_width(s_fl.width, 0, 1);
	if (s_fl.minus == 0)
		counter += ft_putchar(c);
	return (counter);
}

int	strdot(char *str, int dot)
{
	int	counter;

	counter = 0;
	if (dot >= 0)
		counter += putstr_w_prec(str, dot);
	else
		counter += putstr_w_prec(str, ft_strlenpf(str));
	return (counter);
}

int	conv_str(char *str, t_flags s_fl)
{
	int	counter;

	counter = 0;
	if (!str)
		str = "(null)";
	if (s_fl.width > ft_strlenpf(str) && s_fl.zero == 1)
	{
		counter += print_width(s_fl.width, 1, ft_strlenpf(str));
		counter += strdot(str, s_fl.dot);
		return (counter);
	}
	if (s_fl.dot >= 0 && (s_fl.dot > ft_strlenpf(str)))
		s_fl.dot = ft_strlenpf(str);
	if (s_fl.minus == 1)
		counter += strdot(str, s_fl.dot);
	if (s_fl.dot >= 0)
		counter += print_width(s_fl.width, 0, s_fl.dot);
	else
		counter += print_width(s_fl.width, 0, ft_strlenpf(str));
	if (s_fl.minus == 0)
		counter += strdot(str, s_fl.dot);
	return (counter);
}
