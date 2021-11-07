#include "../includes/minishell.h"

void	printlist(t_elist *lst)
{
	t_elist *curr;

	curr = lst;
	if (curr)
	{
		while (curr->next)
		{
			printf("%s\n", curr->key);
			printf("%s\n", curr->value);
			curr = curr->next;
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	*data;
	int		i;

	data = malloc(sizeof(t_data));
	(void)ac;
	(void)av;
	(void)envp;
	i = 0;
	//data->env_list = NULL;
	data->env_list = set_env_list(envp);
	// while (1)
	// {
	// 	data->cmd.str = readline("% ");
	// 	add_history(data->cmd.str);
	// 	data->cmd.cmdline = split(data->cmd.str, ' ', &data->cmd);
	// 	i = 0;
	// 	while(i < data->cmd.i)
	// 		check_cmd(data->cmd.cmdline[i++], &data->cmd, envp);
	// 	free(data->cmd.cmdline);
	// 	free(data->cmd.str);
	// }
}
