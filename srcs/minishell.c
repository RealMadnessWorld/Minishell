#include "../includes/minishell.h"

void	data_init(t_data *d)
{
	d->t = NULL;
	d->cmd.i = 0;
	// d = malloc(sizeof(t_data));
	// d->envars_list = set_envars_list(envp);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)ac;
	(void)av;
	data.envars_list = set_envars_list(envp);
	while (1)
	{
		data_init(&data);
		data.cmd.str = readline(CLR_MGT"💀 What are your orders captain?\n"CLR_RST);
		// printf(CLR_BLU"i am the string:\t %s\n"CLR_RST, data.cmd.str);
		add_history(data.cmd.str);
		split(data.cmd.str, '|', &data.cmd);
		token_creater(&data);
		handle_dollar_sign(&data);
		// printlst(data.t);
		validations(&data);
		everyone_be_freeee(&data);
	}
}
