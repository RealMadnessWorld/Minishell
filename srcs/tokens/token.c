#include "../../includes/minishell.h"

void	token_check(t_tokens *t)
{
	if (is_command(t->str))
		t->token = e_command;
	else if (ft_strcmp(t->str, "|") == 0)
		t->token = e_pipe;
	else if (ft_strncmp(t->str, "\"", 1) == 0)
		t->token = e_quotes;
	else if (ft_strncmp(t->str, "\'", 1) == 0)
		t->token = e_single_quotes;
	else if (ft_strcmp(t->str, ">") == 0)
		t->token = e_bigger;
	else if (ft_strcmp(t->str, "<") == 0)
		t->token = e_smaller;
	else if (ft_strcmp(t->str, "||") == 0)
		t->token = e_or;
	else if (ft_strcmp(t->str, "&&") == 0)
		t->token = e_and;
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
	*tmp = malloc(sizeof(char) * ft_strlen(str));
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

t_tokens	*token_creater(t_data *d)
{
	int			i;
	int			j;
	t_tokens	*tmp;
	t_tokens	*also_tmp;
	char		*str;

	i = 0;
	j = 0;
	also_tmp = d->t;
	while (d->cmd.cmdline[i])
	{
		j = 0;
		while (d->cmd.cmdline[i][j])
		{
			j = token_str_checker(&str, d->cmd.cmdline[i], j);
			token_lstadd_back(&also_tmp, token_lstnew(ft_strdup(str)));
			tmp = token_lstlast(also_tmp);
			token_check(token_lstlast(also_tmp));
			printf("\n\n----------------------------------------------\n----------------------------------------------\n\n");
			printf(CLR_RED"\t\t\tFULL LIST INFO\n"CLR_RST);
			printf("nmbr of nodes: %d\n", token_lstsize(also_tmp));
			printf("list strings:\n\n");
			printlst(also_tmp);
			printf(CLR_RED"\t\t\tLATEST NODE\n"CLR_RST);
			printf("str: %s\n", tmp->str);
			printf("token: %d\n\n", tmp->token);
			free(str);
		}
		i++;
	}
	return (also_tmp);
}