#include "../../includes/minishell.h"

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

void	check_cmd(t_data *d, t_tokens *t)
{
	pid_t pid;
	int	i;
	int	path;

	i = 0;
	d->exec->t = conv_tokens(t);
	d->exec->env = conv_env(d->envars_list);
	d->exec->path = ft_strjoin_path(d->bin_paths[i], "/", d->t->str);
	if (d->nr_pipes == 0)
	{
		while (d->bin_paths[i] != NULL)
		{
			path = access(ft_strjoin_path(d->bin_paths[i], "/", d->t->str), F_OK);
			if (path == 0)
				break ;
			i++;
		}
		if (path == -1 && t->token != e_command)
		{
			printf("command not found: %s\n", t->str);
			return ;
		}
		if (t->token == e_command)
		{
			do_builtin(d, t);
			return ;
		}
		if (t->token == is_nothing)
		{
			pid = fork();
			execve(d->exec->path, d->exec->t, d->exec->env);
			kill(pid, SIGKILL);
		}
	}
	// else
	// 	exec_pipeline();
}

			//ft_child_execve()

			/*problema 1:
				(resolvido mas o execve ainda não funciona)

			problema 2:
				(já tratei das conversões mas a linha 28 não está a funcionar não sei porquê)

			PS: nova função ft_strjoin_path no ficheiro ft_strjoin (top)
			PS1: se o export.c der problemas caga, foi outra cena que eu tava a começar a fazer (não deu problemas)
			PS2: best playstation ever (prefiro a 3 xP)
			PS3: <3
			*/