/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarsenio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 20:13:15 by jarsenio          #+#    #+#             */
/*   Updated: 2021/03/05 20:14:17 by jarsenio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *string)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = (char *)malloc(sizeof(*string) * (ft_strlen(string) + 1));
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
