/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ext.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarsenio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:30:35 by jarsenio          #+#    #+#             */
/*   Updated: 2021/09/10 17:30:37 by jarsenio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	find_extention(char *str, char *ext)
{
	int	i;
	int	x;

	i = ft_strlen(str);
	x = ft_strlen(ext);
	while (i != 0 && str[i] != '.')
	{
		if (str[i] != ext[x])
		{
			return (0);
		}
		i--;
		x--;
	}
	return (1);
}
