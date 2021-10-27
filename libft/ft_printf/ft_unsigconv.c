/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigconv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarsenio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 01:39:39 by jarsenio          #+#    #+#             */
/*   Updated: 2021/04/22 01:39:41 by jarsenio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	insta_fix(t_flags *s_fl, char *str)
{
	int	counter;

	counter = 0;
	if (s_fl->dot <= -1)
		s_fl->dot = ft_strlenpf(str);
	if (s_fl->dot >= 0)
		counter += print_width(s_fl->dot, 1, ft_strlenpf(str));
	return (counter);
}

int	unsig_conv(unsigned num, t_flags s_fl)
{
	int		counter;
	char	*str;

	counter = 0;
	if (s_fl.dot == 0 && num == 0)
	{
		counter += print_width(s_fl.width, 0, 0);
		return (counter);
	}
	str = unsigneditoa(num, 10);
	counter += print_unsigned(str, s_fl);
	free(str);
	return (counter);
}

int	print_unsigned(char *str, t_flags s_fl)
{
	int	counter;

	counter = 0;
	if (s_fl.dot >= 0 && (s_fl.dot < ft_strlenpf(str)))
		s_fl.dot = ft_strlenpf(str);
	if (s_fl.minus == 1)
	{
		counter += insta_fix(&s_fl, str);
		counter += putstr_w_prec(str, s_fl.dot);
	}
	if (s_fl.dot >= 0)
		counter += print_width(s_fl.width, 0, s_fl.dot);
	else
		counter += print_width(s_fl.width, s_fl.zero, ft_strlenpf(str));
	if (s_fl.minus == 0)
	{
		counter += insta_fix(&s_fl, str);
		counter += putstr_w_prec(str, s_fl.dot);
	}
	return (counter);
}
