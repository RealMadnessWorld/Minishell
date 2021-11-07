#include "../includes/minishell.h"

void	do_env(char **envp)
{
    int i = 0;

	while (envp[i])
		printf("%s\n", envp[i++]);
}

static t_elist *add_node(char **line)
{
	t_elist *node;

	node = (t_elist *)malloc(sizeof(t_elist));
	if (line)
	{
			node->key = ft_strdup(line[0]);
			printf("%s\n", node->key);
			node->value = ft_strdup(line[1]);
			printf("%s\n", node->value);
			node->next = NULL;
	}
	return (node);
}

static char **set_line(char *envl)
{
	char **line;
	int	i;

	line = malloc(sizeof(char *) * 3);
	i = 0;
	while (envl[i] != '=')
		i++;
	line[0] = ft_substr(envl, 0, i);
	line[1] = ft_substr(envl, i, (ft_strlen(envl) - i));
	return (line);
}

t_elist *set_env_list(char **envp)
{
	t_elist *list;
	t_elist	*curr;
	char	**line;
	int		i;

	i = 0;
	line = set_line(envp[0]);
	envp = NULL;
	list = NULL;
	curr = add_node(line);
	// list = curr;
	// curr = curr->next;
	// while (envp[i])
	// {
	// 	line = split(envp[i], '=', NULL);
	// 	curr = add_node(line);
	// 	curr = curr->next;
	// 	i++;
	// }
	return (list);
}
