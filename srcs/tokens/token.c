#include "../../includes/minishell.h"

void	token_check(t_tokens *t)
{
	if (is_command(t->str))
	{
		printf("%s is a command ^^\n", t->str);
		t->token = e_command;
	}
	else if (ft_strcmp(t->str, "|"))
	{
		printf("%s is a pipe\n", t->str);
		t->token = e_pipe;
	}
	else if (ft_strcmp(t->str, "\""))
	{
		printf("%s is a quotes\n", t->str);
		t->token = e_quotes;
	}
	else
	{
		printf("%s it's not a command\n", t->str);
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
	tmp = malloc(sizeof(char) * ft_strlen(str));
	while (str[i])
	{
		if (str[i] == '"')
		{
			while (str[i] == '"')
			{
				quote *= -1;
				i++;
			}
		}
		if (str[i] == ' ' && quote != 1)
		{
			while (str[i] == ' ')
				i++;
			(*tmp)[j] = '\0';
			return (x);
		}
		printf("wroking so far\n");
		(*tmp)[j] = str[i];
		i++;
		j++;
	}
	(*tmp)[j] = '\0';
	return (i);
}

void	token_creater(t_cmd *d)
{
	int			i;
	int			j;
	t_tokens	*tmp;
	char		*str;

	d->t = malloc(sizeof(t_tokens));
	i = 0;
	j = 0;
	while (d->cmdline[i][j])
	{
		j = token_str_checker(&str, d->cmdline[i], j);
		printf("hi\n");
		token_lstadd_back(&d->t, token_lstnew(str));
		tmp = token_lstlast(d->t);
	 	token_check(token_lstlast(d->t));
		printf("%s ?==? %s \n", tmp->str, d->cmdline[i]);
		printf("string[%d] is token: %i\n", i, tmp->token);
		printf("\n\n--------------\n\n");
		free(str);
	}
}