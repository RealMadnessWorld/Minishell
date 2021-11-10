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
		t->token = e_quotes
	}
	else
	{
		printf("%s it's not a command\n", t->str);
		t->token = is_nothing;
	}
}

void	token_creater(t_cmd *d)
{
	int			i;
	t_tokens	*tmp;

	d->t = malloc(sizeof(t_tokens));
	i = -1;
	while (++i < d->i)
	{
		token_lstadd_back(&d->t, token_lstnew(d->cmdline[i]));
		tmp = token_lstlast(d->t);
	 	token_check(token_lstlast(d->t));
		if ()
		printf("%s ?==? %s \n", tmp->str, d->cmdline[i]);
		printf("string[%d] is token: %i\n", i, tmp->token);
		printf("\n\n--------------\n\n");
	}
}