#include "../includes/minishell.h"

int	main(int ac, char ** av, char **envp)
{
	t_cmd	cmd;
	int		i;

	(void)ac;
	(void)av;
	cmd.i = 0;
	while (1)
	{
		cmd.str = readline("What is your command?\t\n");
		add_history(cmd.str);
		cmd.cmdline = split(cmd.str, ' ', &cmd);
		i = 0;
			token_creater(&cmd);
		while(cmd.cmdline[i])
		{
			while (cmd.t->next != NULL)
			{
				if (cmd.t->token == e_command)
					check_cmd(cmd.cmdline[i], &cmd, envp);
				cmd.t = cmd.t->next;
			}
			printf("cmd = %s\n", cmd.cmdline[i++]);
		}
		printf("hi i passed you motherfucker! Notice me!!!!\n");
		free(cmd.cmdline);
		free(cmd.str);
	}
}
