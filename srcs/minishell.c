#include "../includes/minishell.h"

static void	printlist(t_evars *lst)
{
	t_evars *curr;

	curr = lst;
	while (curr)
	{
		printf("%s%s\n", curr->key, curr->value);
		curr = curr->next;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	*data;
	int		i;

	data = malloc(sizeof(t_data));
	(void)ac;
	(void)av;
	i = 0;
	data->evars_list = NULL;
	data->evars_list = set_evars_list(envp);
	printlist(data->evars_list);
	while (1)
	{
		data->cmd.str = readline("% ");
		add_history(data->cmd.str);
		data->cmd.cmdline = split(data->cmd.str, ' ', &data->cmd);
		i = 0;
		while(i < data->cmd.i)
			check_cmd(data->cmd.cmdline[i++], &data->cmd, envp);
		free(data->cmd.cmdline);
		free(data->cmd.str);
	}
}
