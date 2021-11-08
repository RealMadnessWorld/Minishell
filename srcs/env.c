#include "../includes/minishell.h"

static t_envars *add_node(char **line)
{
	t_envars *node;

	node = (t_envars *)malloc(sizeof(t_envars));
	if (line)
	{
			node->key = ft_strdup(line[0]);
			node->value = ft_strdup(line[1]);
			node->next = NULL;
			free(line[0]);
			free(line[1]);
	}
	return (node);
}

static char	**set_line(char *envl)
{
	char	**line;
	int		i;

	line = malloc(sizeof(char *) * 3);
	i = 0;
	while (envl[i] != '=')
		i++;
	line[0] = ft_substr(envl, 0, i);
	line[1] = ft_substr(envl, i, (ft_strlen(envl) - i));
	return (line);
}

t_envars	*set_envars_list(char **envp)
{
	t_envars	*list;
	t_envars	*curr;
	char		**line;
	int			i;
	t_envars	*prev;

	i = 0;
	curr = NULL;
	line = set_line(envp[0]);
	curr = add_node(line);
	list = curr;
	while (envp[++i])
	{
		prev = curr;
		curr = curr->next;
		line = set_line(envp[i]);
		curr = add_node(line);
		prev->next = curr;
	}
	return (list);
}

void	add_envars(char *str, t_envars **envars_lst)
{
	char		**line;

	line = set_line(str);


}

void	parse_envars(t_tokens *tkn_lst, t_envars *envars_lst)
{
	t_tokens	*curr;
	int			i;
	int			j;

	curr = tkn_lst;
	i = -1;
	while (curr)
	{
		if (curr->token == e_command)
		{
			while (curr->str[i++])
			{
				if (curr->str[i] == '=')
					add_envar(curr->str, &envars_lst, i);
			}
		}
		i = 0;
		curr = curr->next;
	}
}
