#include "../../includes/minishell.h"

int	count_pipes(t_tokens *t)
{
	t_tokens	*curr;
	int			i;

	curr = t;
	i = 0;
	while (curr)
	{
		if (curr->token == e_pipe)
			i++;
		curr = curr->next;
	}
	return (i);
}
t_tokens	**conv_cmds(t_tokens *t, int nr_pipes)
{
	t_tokens	*curr;
	int			i;
	t_tokens	**new;

	curr = t;
	i = 0;
	new = (t_tokens **)malloc(sizeof(t_tokens *) * nr_pipes + 1);
	new[i] = t;
	i++;
	while (curr)
	{
		if (curr->token == e_pipe)
		{
			new[i] = curr->next;
			i++;
		}
		curr = curr->next;
	}
	return (new);
}

static int	command_size(t_tokens *lst)
{
	int			i;
	t_tokens	*curr;

	i = 0;
	curr = lst;
	while (curr && curr->token != e_pipe)
	{
		curr = curr->next;
		i++;
	}
	return (i);
}

char	**conv_tokens(t_tokens *t)
{
	char		**cmd_lst;
	int			i;
	t_tokens	*curr;

	i = 0;
	cmd_lst = (char **)malloc(sizeof(char *) * (command_size(t) + 1));
	printf("com size %d\n", command_size(t));
	curr = t;
	if (!cmd_lst)
		return (0);
	while (curr && curr->token != e_pipe)
	{
		cmd_lst[i] = ft_strdup(curr->str);
		curr = curr->next;
		i++;
	}
	cmd_lst[i] = NULL;
	return (cmd_lst);
}

char	**conv_env(t_envars *env)
{
	int			i;
	char		**str;
	t_envars	*curr;

	i = 0;
	str = (char **)malloc(sizeof(char *) * (env_lstsize(env) + 1));
	curr = env;
	if (!str)
		return (0);
	while (curr)
	{
		str[i] = ft_strdup(ft_strjoin_path(curr->key, "=", curr->value));
		curr = curr->next;
		i++;
	}
	str[i] = NULL;
	return (str);
}
