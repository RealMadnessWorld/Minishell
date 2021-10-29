#include "minishell.h"

int	main(void)
{
	t_cmd	cmd;
	char	*str;
	int		i;

	while (1)
	{
		str = readline("What is your command?\t\n");
		cmd.cmdline = split(str, ' ', &cmd);
		i = 0;
		while(i < cmd.i)
			check_cmd(cmd.cmdline[i++], &cmd);
		free(cmd.cmdline);
	}
}