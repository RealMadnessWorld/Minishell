/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarsenio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:26:25 by jarsenio          #+#    #+#             */
/*   Updated: 2021/04/28 18:26:29 by jarsenio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	intlen(long int n, int base)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		n = n * -1;
	while (n > 0)
	{
		n = n / base;
		len++;
	}
	return (len);
}

int	unintlen(unsigned long long n, int base)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		n = n * -1;
	while (n > 0)
	{
		n = n / base;
		len++;
	}
	return (len);
}

char	*unsigneditoa(unsigned long long n, int base)
{
	char				*str;
	unsigned long long	len;

	if (n == 0)
		return (ft_strdup("0"));
	len = unintlen(n, base);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (0);
	str[len--] = '\0';
	while (n > 0)
	{
		if ((n % base) < 10)
			str[len] = (n % base) + '0';
		else
			str[len] = (n % base) + 55;
		n = n / base;
		len--;
	}
	return (str);
}

char	*ft_itoapf(long int n)
{
	char	*res;
	size_t	len;

	len = intlen(n, 10);
	res = (char *)malloc(len + 1 * sizeof(char));
	if (!res)
		return (0);
	res[len] = '\0';
	len--;
	if (n == 0)
		res[0] = '0';
	else if (n < 0)
	{
		res[0] = '-';
		n = n * -1;
	}
	while (n > 0)
	{
		res[len] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
	return (res);
}
