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

int	ft_strcmp(char *s1, char *s2)
{
	if (!s1 && !s2)
		return (0);
	while (*s1 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 == '\0')
		return (0);
	else
		return (*(unsigned char *)s1 - *(unsigned char *)s2);
}





















// int	ft_strcmp(char *newstr, char *original)
// {
// 	int	i;
// 	int	len;

// 	i = 0;
// 	len = ft_strlen(original);
// 	while (i < len)
// 	{
// 		if (original[i] != newstr[i])
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }
