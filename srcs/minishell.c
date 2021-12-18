#include "../includes/minishell.h"

int	g_status = 0;
static void	data_init(t_data *d);
static int	skip_spaces_get_cmd(char *str);
static int	free_on_if(char *str);

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)ac;
	(void)av;
	data.envars_list = set_envars_list(envp);
	do_i_have_signal();
	//falta cuidar da primeira linha do subject - n intrepretar ; ou '\'
	while (1)
	{
		data_init(&data);
		data.cmd.str = readline(CLR_MGT"💀 What are your orders captain? "CLR_RST);
		if (*data.cmd.str == ' ' && skip_spaces_get_cmd(data.cmd.str))
			continue ;
		if (*data.cmd.str == '\0' && free_on_if(data.cmd.str))
			continue ;
		add_history(data.cmd.str);
		split(data.cmd.str, '|', &data.cmd);
		token_creater(&data);
		handle_dollar_sign(&data);
		parse_envars(data.t, data.envars_list);
		// printlst(data.t);
		executor(&data, data.t);
		everyone_be_freeee(&data);
	}
	free_envars_list(data.envars_list);
}

static void	data_init(t_data *d)
{
	d->t = NULL;
	d->cmd.i = 0;
	d->nr_pipes = 0;
	d->pipes = NULL;
	d->exec = NULL;
	d->bin_paths = NULL;
	d->fd.in_name = NULL;
	d->fd.out_name = NULL;
}

static int	skip_spaces_get_cmd(char *str)
{
	char *tmp;

	tmp = str;
	while (*tmp == ' ')
		tmp++;
	if (*tmp && ft_isalnum(*tmp))
	{
		free(str);
		str = ft_strdup(tmp);
		return (0);
	}
	free(str);
	str = NULL;
	return (1);
}

static int	free_on_if(char *str)
{
	free(str);
	return (1);
}
