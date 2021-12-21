#include "../../includes/minishell.h"

void	check_vars(t_tokens *t)
{
	t_tokens	*tmp;
	int			i;
	int			x;

	tmp = t;
	while (tmp)
	{
		i = -1;
		x = 0;
		if (tmp->token == is_nothing)
		{
			while (tmp->str[++i] != '\0')
			{
				if (tmp->str[i] == '=')
					x++;
			}
		}
		if (x == 1)
			tmp->token = e_var;
		tmp = tmp->next;
	}
}

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
	else if (ft_strcmp(t->str, ">") == 0)
		t->token = e_bigger;
	else if (ft_strcmp(t->str, "<") == 0)
		t->token = e_smaller;
	else if (ft_strcmp(t->str, ">>") == 0)
		t->token = e_double_bigger;
	else if (ft_strcmp(t->str, "<<") == 0)
		t->token = e_double_smaller;
	else if (ft_strcmp(t->str, "-n") == 0)
		t->token = e_n_flag;
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

int	token_creater(t_data *d)
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
	check_vars(d->t);
	if (handle_quotes(d->t))
		return (1);
	re_check_tokens(d->t);
	if (!set_fd(d->t))
		return (0);
	set_fd_names(d, d->t);
	return (1);
}
