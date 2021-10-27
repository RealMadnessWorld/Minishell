/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_img_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarsenio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:30:25 by jarsenio          #+#    #+#             */
/*   Updated: 2021/09/10 17:30:26 by jarsenio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*chk_img_path(char *path)
{
	if (open((path), O_RDONLY) < 0)
		ft_error(CLR_RED "You're lacking the images... focus please\n" CLR_RST);
	return (path);
}
