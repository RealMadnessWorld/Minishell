#include "../includes/minishell.h"

static void	printlist(t_envars *lst)
{
	t_envars *curr;

	curr = lst;
	while (curr)
	{
		printf("%s%s\n", curr->key, curr->value);
		curr = curr->next;
	}
}

static void printsplit(char **splt)
{
	int	i = 0;

	while (splt[i])
		printf("%s\n", splt[i++]);
}

int	main(int ac, char **av, char **envp)
{
	t_data	*data;
	int		i;

	data = malloc(sizeof(t_data));
	(void)ac;
	(void)av;
	i = 0;
	data->envars_list = NULL;
	data->envars_list = set_envars_list(envp);
	printlist(data->envars_list);
	while (1)
	{
		data->cmd.str = readline("% ");
		add_history(data->cmd.str);
		data->cmd.cmdline = split(data->cmd.str, ' ', &data->cmd);
		printsplit(data->cmd.cmdline);
		i = 0;
		while(i < data->cmd.i)
			check_cmd(data->cmd.cmdline[i++], &data->cmd, envp);
		free(data->cmd.cmdline);
		free(data->cmd.str);
	}
}
