#include "../includes/minishell.h"

e_token	token_check(t_tokens *t)
{
	if (is_command(t) == 1)
	{
		printf("%s is a command ^^\n", t->str);
		return (e_command);
	}
	else
	{
		printf("%s it's not a command\n", t->str);
		return (is_nothing);
	}
}

t_tokens	*token_creater(t_cmd *d)
{
	int			i;
	t_tokens	*tokens;

	tokens = malloc(sizeof(t_tokens));
	i = -1;
	while (i < d->i)
	{
		tokens->str = d->cmdline[++i];
		printf("%s ?==? %s \n", tokens->str, d->cmdline[i]);
		tokens->token = token_check(tokens);
		printf("string[%d] is token: %d\n", i, tokens->token);
	}
	free(tokens);
	return (tokens);
}