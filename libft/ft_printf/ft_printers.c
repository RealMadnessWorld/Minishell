/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarsenio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 18:52:50 by jarsenio          #+#    #+#             */
/*   Updated: 2021/04/14 18:52:53 by jarsenio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	putstr_w_prec(char *s, int dot)
{
	int		i;
	int		counter;

	i = 0;
	counter = 0;
	if (!s)
		return (i);
	while (s[i] != '\0' && i < dot)
	{
		counter += ft_putchar(s[i]);
		i++;
	}
	return (counter);
}

int	print_width(int width, int zero, int size)
{
	int	counter;

	counter = 0;
	while (width - size > 0)
	{
		if (zero == 1)
			counter += ft_putchar('0');
		else
			counter += ft_putchar(' ');
		width--;
	}
	return (counter);
}
