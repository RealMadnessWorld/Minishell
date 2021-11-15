#include "../includes/minishell.h"

void	data_init(t_data *d)
{
	d->cmd.t = NULL;
	d->cmd.i = 0;
	// d = malloc(sizeof(t_data));
	//d->envars_list = NULL;
	// d->envars_list = set_envars_list(envp);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	int		i;

	(void)ac;
	(void)av;
	while (1)
	{
		i = 0;
		data_init(&data);
		data.cmd.str = readline("What is your command:\n");
		printf(CLR_BLU"i am the string: %s\n"CLR_RST, data.cmd.str);
		//add_history(data.cmd.str);
		split(data.cmd.str, '|', &data.cmd);
		// printf(CLR_GRN "hi i passed you motherfucker! Notice me!!!!\n" CLR_RST);


		// while (data.cmd.cmdline[i])
		// {
		// 	printf("str[%d] = %s\n", i, data.cmd.cmdline[i]);
		// 	i++;
		// }


		data.cmd.t = token_creater(&data.cmd);
		while(data.cmd.cmdline[i])
		{
			while (data.cmd.t)
			{
				printf("linked list: %s\n", data.cmd.t->str);
				if (data.cmd.t->token == e_command)
					check_cmd(data.cmd.cmdline[i], &data, envp);
				data.cmd.t = data.cmd.t->next;
			}
			printf("cmd = %s\n", data.cmd.cmdline[i++]);
		}
		everyone_be_freeee(&data);
	}
}
