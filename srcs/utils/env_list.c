#include "../../includes/minishell.h"

t_envars *add_node(char **line)
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

char	**set_line(char *envl)
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

// int main(int ac, char **av, char **envp)
// {
// 	t_data		*data = malloc(sizeof(t_data));
// 	t_tokens	*first = malloc(sizeof(t_tokens));
// 	t_tokens	*second = malloc(sizeof(t_tokens));
// 	t_tokens	*third = malloc(sizeof(t_tokens));
// 	t_envars	*curr;

// 	data->envars_list = NULL;
// 	data->envars_list = set_envars_list(envp);
// 	curr = data->envars_list;
// 	first->str = ft_strdup("primeiro=FIRST");
// 	first->token = e_command;
// 	second->str = ft_strdup("segundo=SECOND");
// 	second->token = e_command;
// 	third->str = ft_strdup("terceiro=THIRD");
// 	third->token = e_command;
// 	first->next = second;
// 	second->next = third;
// 	third->next = NULL;
// 	parse_envars(first, data->envars_list);
// 	while (curr)
// 	{
// 		printf("%s", curr->key);
// 		printf("%s\n", curr->value);
// 		curr = curr->next;
// 	}
// 	curr = data->envars_list;
// 	while (curr)
// 	{
// 		free(curr->key);
// 		free(curr->value);
// 		free(curr);
// 		curr = curr->next;
// 	}
// 	return (0);
// }