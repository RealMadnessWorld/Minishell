/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmeira <fmeira@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 18:58:50 by fmeira            #+#    #+#             */
/*   Updated: 2021/12/30 18:58:51 by fmeira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	do_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 4096);
	if (pwd)
	{
		ft_putendl_fd(pwd, 1);
		free(pwd);
		pwd = NULL;
		return (0);
	}
	else
		return (1);
}
