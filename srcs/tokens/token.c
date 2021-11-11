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

char	*token_str_checker(char *str)
{
	char		*tmp;
	static int	i;
	int			j;
	int 		quote;

	i = 0;
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
			tmp[j] = '\0';
			return (tmp);
		}
		tmp[j] = str[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

void	token_creater(t_cmd *d)
{
	int			i;
	// int			j;
	t_tokens	*tmp;
	char		*str;

	//d->t = malloc(sizeof(t_tokens));
	i = -1;
	// j = -1;
	while (++i < d->i)
	{
		str = token_str_checker(d->cmdline[i]);
		token_lstadd_back(&d->t, token_lstnew(str));
		tmp = token_lstlast(d->t);
	 	token_check(token_lstlast(d->t));
		printf("%s ?==? %s \n", tmp->str, d->cmdline[i]);
		printf("string[%d] is token: %i\n", i, tmp->token);
		printf("\n\n--------------\n\n");
		free(str);
	}
}