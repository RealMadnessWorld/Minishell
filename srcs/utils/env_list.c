#include "../../includes/minishell.h"

t_envars *add_node(char **line)
{
	t_envars *node;

	node = (t_envars *)malloc(sizeof(t_envars));
	if (line)
	{
			node->key = ft_strdup(line[0]);
			if (line[1])
				node->value = ft_strdup(line[1]);
			else
				node->value = NULL;
			node->next = NULL;
			while (*line++)
				free(*line);
			line = NULL;
	}
	return (node);
}

char	**set_line(char *envl)
{
	char	**line;
	int		i;

	i = 0;
	while (envl[i] != '=' && envl[i])
		i++;
	if (envl[i] == '=')
	{
		line = malloc(sizeof(char *) * 3);
		line[0] = ft_substr(envl, 0, i);
		i++;
		line[1] = ft_substr(envl, i, (ft_strlen(envl) - i));
		line[2] = NULL;
		return (line);
	}
	else
	{
		line = malloc(sizeof(char *) * 2);
		line[0] = ft_strdup(envl);
		line[1] = NULL;
		free(envl);
		return (line);
	}
}

t_envars	*set_envars_list(char **envp)
{
	t_envars	*list;
	t_envars	*curr;
	t_envars	*prev;
	char		**line;
	int			i;

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

char		*get_env(t_envars *env, char *str)
{
	t_envars	*curr;

	curr = env;
	if (curr == NULL || !curr)
		return (NULL);
	while (curr)
	{
		if (ft_strcmp(str, curr->key) == 0)
		{
			if (!curr->value)
				return (NULL);
			else
				return (ft_strdup(curr->value));
		}
		curr = curr->next;
	}
	return (NULL);
}

void		set_env(t_envars *env, char *key, char *value)
{
	t_envars	*curr;
	char		**to_add;

	if (!key || !value)
		return ;
	curr = env;
	to_add = malloc(sizeof(char *) * 3);
	to_add[0] = key;
	to_add[1] = value;
	to_add[2] = NULL;
	while (curr)
	{
		if (ft_strcmp(key, curr->key) == 0)
		{
			if (curr->value)
				free(curr->value);
			curr->value = ft_strdup(value);
			free(to_add);
			to_add = NULL;
			return ;
		}
		if (curr->next == NULL)
		{
			curr->next = add_node(to_add);
			return ;
		}
		curr = curr->next;
	}
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
