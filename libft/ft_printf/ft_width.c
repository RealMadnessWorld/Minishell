/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whidth.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarsenio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 18:53:50 by jarsenio          #+#    #+#             */
/*   Updated: 2021/04/14 18:53:15 by jarsenio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_flags	flags_init(void)
{
	t_flags	s_fl;

	s_fl.width = 0;
	s_fl.control = 0;
	s_fl.star = 0;
	s_fl.minus = 0;
	s_fl.zero = 0;
	s_fl.dot = -1;
	s_fl.letter = 0;
	return (s_fl);
}

int	set_prec(const char *str, int i, va_list args, t_flags *s_fl)
{
	i++;
	if (str[i] == '*')
	{
		s_fl->dot = va_arg(args, int);
		i++;
	}
	else
	{
		s_fl->dot = 0;
		while (ck_num(str[i]))
		{
			s_fl->dot = (s_fl->dot * 10) + (str[i] - '0');
			i++;
		}
	}
	return (i);
}

void	set_star(t_flags *s_fl, va_list args)
{
	if (s_fl->star == 1)
		s_fl->width = va_arg(args, int);
	if (s_fl->width < 0)
	{
		s_fl->minus = 1;
		s_fl->zero = 0;
		s_fl->control = 1;
		s_fl->width *= -1;
	}
}

void	set_letter(char c, t_flags *s_fl)
{
	s_fl->letter = c;
}

void	set_width(const char c, t_flags *s_fl)
{
	if (s_fl->star == 1)
	{
		s_fl->width = 0;
	}
	s_fl->width = (s_fl->width * 10) + (c - '0');
}
