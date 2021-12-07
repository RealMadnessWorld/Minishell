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
	g_d->envars_list = set_envars_list(envp);
	g_d->bin_paths = ft_split(get_env(g_d->envars_list, "PATH"), ':');
	do_i_have_signal();
	while (1)
	{
		data_init(&data);
		data.cmd.str = readline(CLR_MGT"💀 What are your orders captain? "CLR_RST);
		add_history(data.cmd.str);
		split(data.cmd.str, '|', &data.cmd);
		token_creater(&data);
		handle_dollar_sign(&data);
		parse_envars(data.t, data.envars_list);
		// parse_envars(data.t, data.envars_list);
		// printlst(data.t);
		validations(&data);
		everyone_be_freeee(&data);
	}
}
