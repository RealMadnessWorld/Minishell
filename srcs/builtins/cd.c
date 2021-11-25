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

static int			change_home_directory(t_envars *env, char *path)
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

	if (change_home_directory(env, path))
		return (0);
	//g_status = 1;
	if (stat(path, &st) == -1)
	{
		return (printf("Error: No such file or directory"));
		//g_status = 127;
	}
	else if (!(st.st_mode & S_IXUSR))
		return (printf("Error: Permission denied"));
	else
		return (printf("Error: Not a directory"));
	if (home)
		free(path);
	return (1);
}

int	do_cd(t_tokens *tkn_lst, t_data *data)
{
	char		*home;
	t_envars	*env;
	char		*str;

	home = NULL;
	env = data->envars_list;
	if (tkn_lst->next->next)
		return (printf("Error: too many arguments\n"));
	if (tkn_lst->next == NULL || tkn_lst->next == '\0'
	|| (!(ft_strcmp(tkn_lst->next->str, "~")))
	|| (!(ft_strcmp(tkn_lst->next->str, "--"))))
	{
		if (!(home = get_env(env, "HOME")))
			return (printf("Error: HOME not set"));
		return (set_directory(env, home, 1));
	}
	if (ft_strcmp(tkn_lst->next->str, "-") == 0)
	{
		str = get_env(env, "OLDPWD");
		set_directory(env, str, 0);
		free(str);
		do_pwd();
		return (1);
	}
	tkn_lst->next = update_home(env, tkn_lst->next->str);
	return (set_directory(env, tkn_lst->next->str, 0));
}

int main(int ac, char **av, char **envp)
{
	t_data		*data;
	int			i = 1;
	t_tokens	*first = malloc(sizeof(t_tokens));
	t_tokens	*second = malloc(sizeof(t_tokens));
	t_tokens	*third = malloc(sizeof(t_tokens));
	t_tokens	*curr = first;

	first->str = ft_strdup("cd");
	second->str = ft_strdup("..");
	third->str = ft_strdup("test");
	first->next = second;
	second->next = third;
	third->next = NULL;

	data = malloc(sizeof(t_data));
	data->envars_list = set_envars_list(envp);
	do_cd(first, data);
	do_pwd();
	do_env(data->envars_list);
//	printf("11111\t11111\t11111\t11111\t11111\t11111\t11111\t11111\t11111\n");
//	printf("22222\t22222\t22222\t22222\t22222\t22222\t22222\t22222\t22222\n");

	return (0);
}
