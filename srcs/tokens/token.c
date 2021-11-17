#include "../../includes/minishell.h"

void	re_check_tokens(t_tokens *t)
{
	t_tokens	*tmp;

	tmp = t;
	while (tmp)
	{
		if (tmp->token == is_nothing)
			token_check(tmp);
		tmp = tmp->next;
	}
}

void	token_check(t_tokens *t)
{
	if (is_command(t->str))
		t->token = e_command;
	else if (ft_strcmp(t->str, "|") == 0)
		t->token = e_pipe;
	// else if (ft_strncmp(t->str, "\"", 1) == 0)
	// 	t->token = e_quotes;
	// else if (ft_strncmp(t->str, "\'", 1) == 0)
	// 	t->token = e_single_quotes;
	else if (ft_strcmp(t->str, ">") == 0)
		t->token = e_bigger;
	else if (ft_strcmp(t->str, "<") == 0)
		t->token = e_smaller;
	else if (ft_strcmp(t->str, ">>") == 0)
		t->token = e_double_bigger;
	else if (ft_strcmp(t->str, "<<") == 0)
		t->token = e_double_smaller;
	else
		t->token = is_nothing;
}

int	token_str_checker(char **tmp, char *str, int x)
{
	int	i;
	int	quotes;
	int	j;

	i = x;
	j = 0;
	quotes = 0;
	*tmp = malloc(sizeof(char) * ft_strlen(str) + 1);
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			quotes = str_quotes_checker(i, str, quotes);
		if (str[i] == ' ' && quotes == 0)
		{
			while (str[i] == ' ')
				i++;
			(*tmp)[j] = '\0';
			return (i);
		}
		(*tmp)[j] = str[i];
		i++;
		j++;
	}
	(*tmp)[j] = '\0';
	return (i);
}

void	token_creater(t_data *d)
{
	int			i;
	int			j;
	char		*str;

	i = 0;
	j = 0;
	while (d->cmd.cmdline[i])
	{
		j = 0;
		while (d->cmd.cmdline[i][j])
		{
			j = token_str_checker(&str, d->cmd.cmdline[i], j);
			token_lstadd_back(&d->t, token_lstnew(ft_strdup(str)));
			token_check(token_lstlast(d->t));
			free(str);
		}
		i++;
	}
	handle_quotes(d->t);
	re_check_tokens(d->t);
}