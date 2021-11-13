#include "../../includes/minishell.h"

void	token_check(t_tokens *t)
{
	if (is_command(t->str))
	{
		// printf("%s is a command ^^\n", t->str);
		t->token = e_command;
	}
	else if (ft_strcmp(t->str, "|"))
	{
		// printf("%s is a pipe\n", t->str);
		t->token = e_pipe;
	}
	else if (ft_strcmp(t->str, "\""))
	{
		// printf("%s is a quotes\n", t->str);
		t->token = e_quotes;
	}
	else
	{
		// printf("%s it's not a command\n", t->str);
		t->token = is_nothing;
	}
}

int	token_str_checker(char **tmp, char *str, int x)
{
	static int	i;
	int			j;
	int 		quote;

	i = x;
	j = 0;
	quote = -1;
	*tmp = malloc(sizeof(char) * ft_strlen(str));
	while (str[i])
	{
		if (str[i] == '"')
			quote *= -1;
		if (str[i] == ' ' && quote != 1)
		{
			while (str[i] == ' ')
				i++;
			(*tmp)[j] = '\0';
			return (i);
		}
		// printf("wroking so far\n");
		(*tmp)[j] = str[i];
		i++;
		j++;
	}
	(*tmp)[j] = '\0';
	return (i);
}

void printlst(t_tokens *also_tmp)
{
	t_tokens	*curr;

	curr = also_tmp;
	while (curr)
	{
		printf("%s\n", curr->str);
		curr = curr->next;
	}
}
t_tokens	*token_creater(t_cmd *d)
{
	int			i;
	int			j;
	t_tokens	*tmp;
	t_tokens	*also_tmp;
	char		*str;

	i = 0;
	j = 0;
	d->t = NULL;
	also_tmp = d->t;
	while (d->cmdline[i])
	{
		j = 0;
		while (d->cmdline[i][j])
		{
			j = token_str_checker(&str, d->cmdline[i], j);
			token_lstadd_back(&also_tmp, token_lstnew(ft_strdup(str)));
			tmp = token_lstlast(also_tmp);
			token_check(token_lstlast(also_tmp));
			printf("\n\n--------------\n--------------\n\n");
			printf("\t\t\tFULL LIST INFO\n");
			printf("nmbr of nodes: %d\n", token_lstsize(also_tmp));
			printf("list strings:\n\n");
			printlst(also_tmp);
			printf("\t\t\tLATEST NODE\n");
			printf("str: %s\n", tmp->str);
			printf("token: %d\n", tmp->token);
			free(str);
		}
		token_lstadd_back(&also_tmp, token_lstnew("|"));
		token_check(token_lstlast(also_tmp));
		i++;
	}
	return (also_tmp);
}