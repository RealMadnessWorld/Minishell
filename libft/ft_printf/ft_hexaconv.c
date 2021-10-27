/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexaconv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarsenio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 05:09:15 by jarsenio          #+#    #+#             */
/*   Updated: 2021/04/22 05:09:20 by jarsenio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	hexa_print(t_flags s_fl, char *str)
{
	int	counter;

	counter = 0;
	if (s_fl.dot >= 0 && (s_fl.dot < ft_strlenpf(str)))
		s_fl.dot = ft_strlenpf(str);
	if (s_fl.dot >= 0)
		counter += print_width(s_fl.width, 0, s_fl.dot);
	else
		counter += print_width(s_fl.width, s_fl.zero, ft_strlenpf(str));
	if (s_fl.minus == 0)
	{
		if (s_fl.dot >= 0)
			counter += print_width(s_fl.dot, 1, ft_strlenpf(str));
		counter += putstr_w_prec(str, ft_strlenpf(str));
	}
	return (counter);
}

int	hexa_conv(unsigned int num, int caps, t_flags s_fl)
{
	int		counter;
	char	*str;

	counter = 0;
	if (num == 0 && s_fl.dot == 0)
	{
		counter += print_width(s_fl.width, 0, 0);
		return (counter);
	}
	str = unsigneditoa(num, 16);
	if (caps == 0)
		str = ft_tolowerpf(str);
	if (s_fl.minus == 1)
	{
		if (s_fl.dot >= 0)
			counter += print_width(s_fl.dot, 1, ft_strlenpf(str));
		counter += putstr_w_prec(str, ft_strlenpf(str));
	}
	counter += hexa_print(s_fl, str);
	free(str);
	return (counter);
}
