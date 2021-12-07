#include "../../includes/minishell.h"

int		is_builtin(t_tokens *t)
{
	if (ft_strcmp(t->str, "cd") == 0)
		return (1);
	if (ft_strcmp(t->str, "echo") == 0)
		return (1);
	if (ft_strcmp(t->str, "pwd") == 0)
		return (1);
	// if (ft_strcmp(t->str, "export") == 0)
		return (1);
	// if (ft_strcmp(t->str, "unset") == 0)
		return (1);
	if (ft_strcmp(t->str, "env") == 0)
		return (1);
	if (ft_strcmp(t->str, "exit") == 0)
		return (1);
	return (0);
}

void	do_builtin(t_data *d, t_tokens *t)
{
	if (ft_strcmp(t->str, "cd") == 0)
		do_cd(t, d->envars_list);
	if (ft_strcmp(t->str, "echo") == 0)
		echo_fun(t);
	if (ft_strcmp(t->str, "pwd") == 0)
		do_pwd();
	// if (ft_strcmp(t->str, "export") == 0)
	// 	do_export(d->envars_list, t->next->str);
	// if (ft_strcmp(t->str, "unset") == 0)
	// 	do_unset(d->envars_list, t->next->str);
	if (ft_strcmp(t->str, "env") == 0)
		do_env(d->envars_list);
	if (ft_strcmp(t->str, "exit") == 0)
		exit_func(d);
}

int	check_cmd(t_data *d, t_tokens *t)
{
	int	i;
	int	path;

	i = 0;
	if (d->nr_pipes->nr_pipes == 0)
	{
		while (g_d->bin_paths[i] != NULL)
		{
			path = access(ft_strjoin_path(d->bin_paths[i], "/", d->t->str), F_OK);
			if (path == 0)
				break ;
			i++;
		}
		if (path == -1 && is_builtin(t))
		{
			printf("command not found: %s\n", t->str);
			return (-1);
		}
		if (is_builtin(t))
		{
			do_builtin(d, t);
			exit(0);
		}
		else
			ft_child_execve()
			//problema 1:
			//	- o execve mata o processo ao usar,
			//		entao é preciso fazer um fork e executar o comando na child:
			//execve(ft_strjoin_path(g_d->bin_paths[i], "/", g_d->t->str), ???, d->envars_list);

			//problema 2:
			//	- o segundo parametro do execve é um char **, e nos temos uma linked list.

			//PS: nova função ft_strjoin_path no ficheiro ft_strjoin
			//PS1: se o export.c der problemas caga, foi outra cena que eu tava a começar a fazer (printar a lista sorted, sem dar sort);
			//PS2: best playstation ever
			//PS3: <3
	}
	else
		exec_pipeline();
}

