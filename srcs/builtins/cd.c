/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmeira <fmeira@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 18:19:27 by fmeira            #+#    #+#             */
/*   Updated: 2022/01/03 20:16:09 by fmeira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*update_home(t_envars *env, char *path)
{
	char		*tmp;
	char		*tmp2;

	if (!ft_strncmp(path, "~/", 2) || (*path == '~' && (ft_strlen(path) == 1)))
	{
		tmp = get_env(env, "HOME");
		if (tmp)
		{
			tmp2 = ft_substr(path, 1, ft_strlen(path));
			free(path);
			path = ft_strjoin(tmp, tmp2);
			free(tmp2);
			free(tmp);
			return (path);
		}
	}
	return (path);
}

static int	change_dir_update_pwds(t_envars *env, char *path)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!chdir(path))
	{
		if (pwd)
		{
			set_env(env, ft_strdup("OLDPWD"), pwd);
		}
		pwd = getcwd(NULL, 0);
		if (pwd)
		{
			set_env(env, ft_strdup("PWD"), pwd);
		}
		return (1);
	}
	free(pwd);
	return (0);
}

static int	set_directory(t_envars *env, char *path, int home)
{
	struct stat	st;

	if (change_dir_update_pwds(env, path))
	{
		if (home)
			free(path);
		return (0);
	}
	g_g.status = 1;
	if (stat(path, &st) == -1)
	{
		g_g.status = 1;
		print_error(path, ": No such file or directory\n");
	}
	else if (!(st.st_mode & S_IXUSR))
		printf("Error: Permission denied\n");
	else
		printf("Error: Not a directory\n");
	if (home)
		free(path);
	return (g_g.status);
}

static int	cd_minus(t_envars *env)
{
	char		*old_pwd;

	old_pwd = get_env(env, "OLDPWD");
	if (!old_pwd)
		return (print_error(NULL, "Error: OLDPWD not set\n"));
	set_directory(env, old_pwd, 0);
	free(old_pwd);
	do_pwd();
	return (1);
}

int	do_cd(t_tokens *tkn_lst, t_envars *env)
{
	char		*home;

	home = NULL;
	if (tkn_lst->next == NULL || tkn_lst->next->str[0] == '\0'
		|| tkn_lst->next->str[0] == '\n'
		|| (!(ft_strcmp(tkn_lst->next->str, "~")))
		|| (!(ft_strcmp(tkn_lst->next->str, "--"))))
	{
		home = get_env(env, "HOME");
		if (!home)
			return (print_error(NULL, "Error: HOME not set\n"));
		return (set_directory(env, home, 1));
	}
	if (ft_strcmp(tkn_lst->next->str, "-") == 0)
		return (cd_minus(env));
	tkn_lst->next->str = update_home(env, tkn_lst->next->str);
	return (set_directory(env, tkn_lst->next->str, 0));
}
