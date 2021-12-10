#include "../../includes/minishell.h"

static char			*update_home(t_envars *env, char *path)
{
	char		*tmp;
	char		*tmp2;

	if (!ft_strncmp(path, "~/", 2))
	{
		if ((tmp = get_env(env, "HOME")))
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

static int			change_dir_update_pwds(t_envars *env, char *path)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!chdir(path))
	{
		if (pwd)
		{
			set_env(env, "OLDPWD", pwd);
			free(pwd);
		}
		pwd = getcwd(NULL, 0);
		if (pwd)
		{
			set_env(env, "PWD", pwd);
			free(pwd);
		}
		return (1);
	}
	free(pwd);
	return (0);
}

static int			set_directory(t_envars *env, char *path, int home)
{
	struct stat	st;

	if (change_dir_update_pwds(env, path))
		return (0);
	//g_status = 1;
	if (stat(path, &st) == -1)
	{
		return (printf("Error: No such file or directory\n"));
		//g_status = 127;
	}
	else if (!(st.st_mode & S_IXUSR))
		return (printf("Error: Permission denied\n"));
	else
		return (printf("Error: Not a directory\n"));
	if (home)
		free(path);
	return (0);
}

int	do_cd(t_tokens *tkn_lst, t_envars *env)
{
	char		*home;
	char		*old_pwd;

	home = NULL;
	if (tkn_lst->next && tkn_lst->next->next
		&& tkn_lst->next->next->token != e_pipe)
		return (printf(CLR_RED"What am I? A multitasker? 👿\n"CLR_RST));
	if (tkn_lst->next == NULL || tkn_lst->next->str[0] == '\0'
	|| tkn_lst->next->str[0] == '\n'
	|| (!(ft_strcmp(tkn_lst->next->str, "~")))
	|| (!(ft_strcmp(tkn_lst->next->str, "--"))))
	{
		home = get_env(env, "HOME");
		if (!home)
			return (printf("Error: HOME not set\n"));
		return (set_directory(env, home, 1));
	}
	if (ft_strcmp(tkn_lst->next->str, "-") == 0)
	{
		old_pwd = get_env(env, "OLDPWD");
		if (!old_pwd)
			return (printf("Error: OLDPWD not set\n"));
		set_directory(env, old_pwd, 0);
		free(old_pwd);
		do_pwd();
		return (1);
	}
	tkn_lst->next->str = update_home(env, tkn_lst->next->str);
	return (set_directory(env, tkn_lst->next->str, 0));
}

// int main(int ac, char **av, char **envp)
// {
// 	t_data		*data;
// 	int			i = 1;
// 	t_tokens	*first = malloc(sizeof(t_tokens));
// 	t_tokens	*second = malloc(sizeof(t_tokens));
// 	// t_tokens	*third = malloc(sizeof(t_tokens));
// 	t_tokens	*curr = first;

// 	data = malloc(sizeof(t_data));
// 	data->envars_list = set_envars_list(envp);
// 	first->str = ft_strdup("cd");
// 	second->str = ft_strdup("exit.c");
// 	// third->str = ft_strdup("test");
// 	first->next = second;
// 	second->next = NULL;
// 	// third->next = NULL;

// 	printf("PWD = %s\n", get_env(data->envars_list, "PWD"));
// 	printf("OLDPWD = %s\n", get_env(data->envars_list, "OLDPWD"));
// 	do_cd(first, data->envars_list);
// 	// do_pwd();
// 	printf("PWD = %s\n", get_env(data->envars_list, "PWD"));
// 	printf("OLDPWD = %s\n", get_env(data->envars_list, "OLDPWD"));
// 	// do_env(data->envars_list);
// //	printf("11111\t11111\t11111\t11111\t11111\t11111\t11111\t11111\t11111\n");

// 	return (0);
// }
