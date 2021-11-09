#include "../includes/minishell.h"

static int	check_q_count(t_tokens *tkn)
{
	int			sq_counter;
	int			dq_counter;
	t_tokens	*curr;
	int			i;

	curr = tkn;
	sq_counter = 0;
	dq_counter = 0;
	i = 0;
	while (curr)
	{
		while(curr->str[i])
		{
			if (curr->str[i] == "'")
				sq_counter++;
			else if (curr->str[i] == '"')
				dq_counter++;
			i++;
		}
		curr = curr->next;
	}
	if (sq_counter % 2 || dq_counter % 2)
		return (1);
	return (0);
}

static void	parse_dbquotes(t_tokens	*tkn)
{
	t_tokens	*curr;
	char		*newstr;

	curr = tkn;
	if (check_q_count(curr))
		printf("error: open quotes\n");
	while (c)
}

void	check_quotes(t_data *data)
{
	t_tokens	*curr;
	int			i;

	i = 0;
	curr = data->token_list;
	while (curr)
	{
		while(curr->str[i])
		{
			if (curr->str[i] == "'")
				parse_dbquotes(curr, i);
			else if (curr->str[i] == "\"")
				parse_sgquotes(curr, i);
			j++;
		}
		i++;
	}
}
