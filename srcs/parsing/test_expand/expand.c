#include "../../../includes/minishell.h"

static int	check_dollar(char *str, int *end)
{
	int		i;
	char	*tmp;
	int		dollar_end;

	i = -1;
	tmp = str;
	dollar_end = *end;
	while (tmp[++i])
	{
		if (tmp[i] == '$')
		{
			if (!(tmp[i + 1]))
				return (-1);
			dollar_end = i;
			while (tmp[dollar_end] != ' ' && tmp[dollar_end])
				dollar_end++;
			return (i);
		}
	}
	return (-1);
}

char	*find_var(char *str, int start, int end, t_data *data)
{
	int			len;
	char		*to_find;
	int			i;
	int			j;
	t_envars	*curr;

	len = end - start;
	to_find = ft_calloc(++len, sizeof(char));
	i = 0;
	j = 0;
	curr = data->envars_list;
	while (len--)
		to_find[i++] = str[++start];
	while (curr)
	{
		if (ft_strcmp(curr->key, to_find))
			return (curr->value);
		curr = curr->next;
	}
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
	while (j < ft_strlen(str))
		new[i] = str[j++];
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
		while (++j < ft_strlen(str_to_fit))
			new[i++] = str_to_fit[j];
		j = end;
		while (j < ft_strlen(str))
			new[i] = str[j++];
		new[i] = '\0';
	}
	else
		new = remove_dollar_install_communism(str, start, end);
	return (new);
}

int	handle_dollar_sign(t_data *data)
{
	int			dollar_start;
	int			dollar_end;
	t_tokens	*curr;
	char		*new;

	curr = data->t;
	dollar_end = 0;
	while (curr)
	{
		if (curr->token != e_single_quotes)
		{
			dollar_start = check_dollar(curr->str, &dollar_end);
			if (dollar_start == -1)
				continue ;
			else
			{
				new = expand_dollar(data, curr->str, dollar_start, dollar_end);
				free(curr->str);
				curr->str = NULL;
				curr->str = new;
			}
		}
		curr = curr->next;
	}
	return (0);
}

int main(int ac, char **av)
{
	t_data		*data = malloc(sizeof(t_data));
	t_tokens	*first = malloc(sizeof(t_tokens));
	t_tokens	*second = malloc(sizeof(t_tokens));
	t_tokens	*third = malloc(sizeof(t_tokens));
	t_tokens	*curr = first;
	int			i = 0;

	data->t = first;
	first->str = ft_strdup("$LOGNAME");
	second->str = ft_strdup("$SHELL");
	third->str = ft_strdup("$SHLVL");
	first->next = second;
	second->next = third;
	third->next = NULL;

	handle_dollar_sign(data);
	while (curr)
	{
		printf("str\t%d = %s\n", i, curr->str);
		i++;
		curr = curr->next;
	}
	curr = first;
	while (curr)
	{
		free(curr->str);
		free(curr);
		curr = curr->next;
	}
	return (0);
}
