#include "../../includes/minishell.h"

static int	get_limits(char *str, int i)
{
	char	*tmp;

	tmp = str;
	while (tmp[++i])
	{
		if (!(ft_isalnum(tmp[i + 1])))
			return (i);
	}
	return (--i);
}

char	*find_var(char *str, int start, int end, t_data *data)
{
	int			len;
	int			i;
	char		*to_find;
	t_envars	*curr;

	len = end - start;
	to_find = ft_calloc(++len, sizeof(char));
	i = 0;
	curr = data->envars_list;
	while (--len)
		to_find[i++] = str[++start];
	while (curr)
	{
		if (!(ft_strcmp(curr->key, to_find)))
		{
			free(to_find);
			return ((curr->value) + 1);
		}
		curr = curr->next;
	}
	free(to_find);
	return (NULL);
}

static char	*remove_dollar_install_communism(char *str, int start, int end)
{
	int		len;
	char	*new;
	int		i;
	int		j;

	i = -1;
	j = -1;
	len = (ft_strlen(str) - (end - start));
	new = ft_calloc(++len, sizeof(char));
	while (++i < start)
		new[i] = str[i];
	j = ++end;
	while (j < (int)ft_strlen(str))
		new[i++] = str[j++];
	new[i] = '\0';
	return (new);
}

char	*expand_dollar(t_data *data, char *str, int start, int end)
{
	char	*str_to_fit;
	int		len;
	char	*new;
	int		i;
	int		j;

	str_to_fit = find_var(str, start, end, data);
	i = -1;
	j = -1;
	if (str_to_fit)
	{
		len = ((ft_strlen(str) - (end - start)) + ft_strlen(str_to_fit));
		new = ft_calloc(++len, sizeof(char));
		while (++i < start)
			new[i] = str[i];
		while (++j < (int)ft_strlen(str_to_fit))
			new[i++] = str_to_fit[j];
		j = ++end;
		while (j < (int)ft_strlen(str))
			new[i++] = str[j++];
		new[i] = '\0';
	}
	else
		new = remove_dollar_install_communism(str, start, end);
	return (new);
}

int	handle_dollar_sign(t_data *data)
{
	int			end;
	t_tokens	*curr;
	int			i;

	curr = data->t;
	while (curr)
	{
		i = -1;
		if (curr->token != e_single_quotes)
		{
			while (curr->str[++i])
			{
				if (curr->str[i] == '$')
				{
					end = get_limits(curr->str, i);
					add(curr, expand_dollar(data, curr->str, i, end));
					i = -1;
				}
			}
		}
		curr = curr->next;
	}
	return (0);
}

// int main(int ac, char **av, char **envp)
// {
// 	t_data		*data = malloc(sizeof(t_data));
// 	t_tokens	*first = malloc(sizeof(t_tokens));
// 	t_tokens	*second = malloc(sizeof(t_tokens));
// 	t_tokens	*third = malloc(sizeof(t_tokens));
// 	t_tokens	*curr = first;
// 	t_envars	*elist;
// 	int			i = 0;

// 	data->t = first;
// 	data->envars_list = set_envars_list(envp);
// 	elist = data->envars_list;

// 	first->str = ft_strdup("$LOGNAM $SHELL $SHLVL cenas");
// 	second->str = ft_strdup("principio $SHELL fim");
// 	third->str = ft_strdup("cenas $SHLVL mais um sem $nada.");
// 	first->next = second;
// 	second->next = third;
// 	third->next = NULL;

// 	handle_dollar_sign(data);

// 	// while (elist)
// 	// {
// 	// 	printf("%s%s\n", elist->key, elist->value);
// 	// 	elist = elist->next;
// 	// }
// 	while (curr)
// 	{
// 		printf("str\t%d = %s\n", i, curr->str);
// 		i++;
// 		curr = curr->next;
// 	}
// 	curr = first;
// 	while (curr)
// 	{
// 		free(curr->str);
// 		free(curr);
// 		curr = curr->next;
// 	}
// 	return (0);
// }
