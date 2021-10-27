/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_num_gen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarsenio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 19:22:57 by jarsenio          #+#    #+#             */
/*   Updated: 2021/09/11 19:22:59 by jarsenio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	random_num(int lower, int upper)
{
	int	num;

	srand(time(0));
	num = (rand() % (upper - lower + 1)) + lower;
	return (num);
}
