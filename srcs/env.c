#include "../includes/minishell.h"

void	do_env(char **envp)
{
    int i = 0;

	while (envp[i])
		printf("%s\n", envp[i++]);
}

static t_evars *add_node(char **line)
{
	t_evars *node;

	node = (t_evars *)malloc(sizeof(t_evars));
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

t_evars	*set_evars_list(char **envp)
{
	t_evars *list;
	t_evars	*curr;
	char	**line;
	int		i;
	t_evars	*prev;

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
