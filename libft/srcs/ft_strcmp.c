/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmeira <fmeira@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 17:32:59 by fmeira            #+#    #+#             */
/*   Updated: 2021/11/09 00:43:47 by fmeira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strcmp(char *newstr, char *original)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(original);
	while (i < len)
	{
		if (original[i] != newstr[i])
			return (0);
		i++;
	}
	return (1);
}
