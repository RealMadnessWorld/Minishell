#include "../includes/minishell.h"

void	data_init(t_data *d)
{
	d->t = NULL;
	d->cmd.i = 0;
	d->nr_pipes = 0;
	d->pipes = NULL;
	d->exec = NULL;
	d->bin_paths = NULL;
	// d = malloc(sizeof(t_data));
	// d->envars_list = set_envars_list(envp);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)ac;
	(void)av;
	data.envars_list = set_envars_list(envp);
	do_i_have_signal();
	while (1)
	{
		data_init(&data);
		data.cmd.str = readline(CLR_MGT"💀 What are your orders captain? "CLR_RST);
		add_history(data.cmd.str);
		split(data.cmd.str, '|', &data.cmd);
		if (token_creater(&data))
		{
			everyone_be_freeee(&data);
			continue ;
		}
		handle_dollar_sign(&data);
		parse_envars(data.t, data.envars_list);
		// printlst(data.t);
		executor(&data, data.t);
		everyone_be_freeee(&data);
	}
	free_envars_lst(data.envars_list);
}
