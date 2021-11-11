#include "../includes/minishell.h"

void	data_init(t_data *d)
{
	d = malloc(sizeof(t_data));
	d->cmd.i = 0;
	d->envars_list = NULL;
	// d->envars_list = set_envars_list(envp);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	int		i;

	(void)ac;
	(void)av;
	i = 0;
	while (1)
	{
		data_init(&data);
		data.cmd.str = readline("What is your command:\n");
		add_history(data.cmd.str);
		data.cmd.cmdline = split(data.cmd.str, '|', &data.cmd);
		printf("hi i passed you motherfucker! Notice me!!!!\n");
		token_creater(&data.cmd);
		while(data.cmd.cmdline[i])
		{
			while (data.cmd.t->next != NULL)
			{
				if (data.cmd.t->token == e_command)
					check_cmd(data.cmd.cmdline[i], &data.cmd, envp);
				data.cmd.t = data.cmd.t->next;
			}
			printf("cmd = %s\n", data.cmd.cmdline[i++]);
		}
		free(data.cmd.cmdline);
		free(data.cmd.str);
	}
}
