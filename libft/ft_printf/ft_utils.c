/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarsenio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 18:53:05 by jarsenio          #+#    #+#             */
/*   Updated: 2021/04/14 18:53:08 by jarsenio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_strlenpf(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *string)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = (char *)malloc(sizeof(*string) * (ft_strlenpf(string) + 1));
	if (!ptr)
		return (NULL);
	while (string[i] != '\0')
	{
		ptr[i] = string[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_tolowerpf(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] = str[i] + 32;
		i++;
	}
	return (str);
}

int	zero_neg(t_flags s_fl)
{
	int	counter;

	counter = 0;
	if (s_fl.dot < s_fl.width && s_fl.zero == 0 && s_fl.dot >= 0)
	{		
		counter += print_width(s_fl.dot, 1, 0);
		counter += print_width(s_fl.width, 0, s_fl.dot);
	}
	else if (s_fl.width >= 0 && s_fl.dot <= -1 && s_fl.zero == 0)
	{
		counter += print_width(1, 1, 0);
		counter += print_width(s_fl.width, 0, 1);
	}
	else if (s_fl.dot >= 0 && s_fl.width == 0)
		counter += print_width(s_fl.dot, 1, 0);
	else if (s_fl.dot < s_fl.width && s_fl.zero == 1 && s_fl.dot >= 0)
		counter += print_width(s_fl.width, s_fl.zero, 0);
	else if (s_fl.dot >= s_fl.width)
		counter += print_width(s_fl.dot, 1, 0);
	else if (s_fl.zero == 1)
		counter += print_width(s_fl.width, 1, 0);
	else
		counter += ft_putchar('0');
	return (counter);
}

int	zero_posi(t_flags s_fl)
{
	int	counter;

	counter = 0;
	if (s_fl.dot < s_fl.width && s_fl.zero == 0 && s_fl.dot >= 0)
	{
		counter += print_width(s_fl.width, 0, s_fl.dot);
		counter += print_width(s_fl.dot, 1, 0);
	}
	else if (s_fl.width >= 0 && s_fl.dot <= -1 && s_fl.zero == 0)
	{
		counter += print_width(s_fl.width, 0, 1);
		counter += print_width(1, 1, 0);
	}
	else if (s_fl.dot >= 0 && s_fl.width == 0)
		counter += print_width(s_fl.dot, 1, 0);
	else if (s_fl.dot < s_fl.width && s_fl.zero == 1 && s_fl.dot >= 0)
		counter += print_width(s_fl.width, s_fl.zero, 0);
	else if (s_fl.dot >= s_fl.width)
		counter += print_width(s_fl.dot, 1, 0);
	else if (s_fl.zero == 1)
		counter += print_width(s_fl.width, 1, 0);
	else
		counter += ft_putchar('0');
	return (counter);
}
