#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_data	*data;
	int		i;

	data = malloc(sizeof(t_data));
	(void)ac;
	(void)av;
	data->cmd.i = 0;
	i = 0;
	data->envars_list = NULL;
	// data->envars_list = set_envars_list(envp);
	while (1)
	{
		data->cmd.str = readline("What is your command:\n");
		add_history(data->cmd.str);
		data->cmd.cmdline = split(data->cmd.str, ' ', &data->cmd);
		token_creater(&data->cmd);
		while(data->cmd.cmdline[i])
		{
			while (data->cmd.t->next != NULL)
			{
				if (data->cmd.t->token == e_command)
					check_cmd(data->cmd.cmdline[i], &data->cmd, envp);
				data->cmd.t = data->cmd.t->next;
			}
			printf("cmd = %s\n", data->cmd.cmdline[i++]);
		}
		printf("hi i passed you motherfucker! Notice me!!!!\n");
		free(data->cmd.cmdline);
		free(data->cmd.str);
	}
}
