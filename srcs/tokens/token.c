#include "../../includes/minishell.h"

void	token_check(t_tokens *t)
{
	if (is_command(t->str))
		t->token = e_command;
	else if (ft_strcmp(t->str, "|") == 0)
		t->token = e_pipe;
	else if (ft_strncmp(t->str, "\"", 1) == 0)
		t->token = e_quotes;
	else
		t->token = is_nothing;
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
	int			i;

	i = 0;
	curr = also_tmp;
	while (curr)
	{
		printf(CLR_CYN"->\tnode [%i] %s\n"CLR_RST, i, curr->str);
		curr = curr->next;
		i++;
	}
	printf("\n");
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