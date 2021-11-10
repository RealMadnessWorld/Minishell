#include "../includes/minishell.h"

static int	check_q_count(t_tokens *tkn, char aspas)
{
	int			q_counter;
	t_tokens	*curr;
	int			i;
	int			to_malloc;

	curr = tkn;
	q_counter = 0;
	i = 0;
	to_malloc = 0;
	while (curr)
	{
		while(curr->str[i])
		{
			if (curr->str[i] == aspas)
				q_counter++;
			else if (curr->str[i] != aspas || (curr->str[i] == aspas
					&& (q_counter % 2)))
				to_malloc++;
			i++;
		}
		curr = curr->next;
	}
	if (q_counter % 2)
	{
		printf("error: open quotes\n");
		return (1);
	}
	return (to_malloc);
}

static int	parse_dbquotes(t_tokens	**tkn, int i)
{
	// t_tokens	*curr;
	// char		*newstr;
	// t_bool		iter;
	// int			pos;

	// curr = *tkn;
	// iter = true;
	// pos = i + 1;
	// newstr = NULL;
	// while (iter && curr)
	// {
	// 	if (curr->str[pos] != '"')
	// 	{
	// 		newstr = append_char(newstr, check_q_count(curr));
	// 	}
	// }
	int i = 0;
	int x = 0;
	int j = 0;
	char *str;
	char *also_str;

	str = (*tkn)->str;
	also_str = (*tkn)->str;
	while(also_str[j] != '\0')
	{
		while(also_str[j] == '"')
		{
			j++;
			x++;
		}
		(*tkn)->str[i] = str[i + x];
		i++;
		j++;
	}
	(*tkn)->str[i] = '\0';
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
			{
				if (parse_dbquotes(&curr, i)

			else if (curr->str[i] == '"')
				i = parse_sgquotes(&curr, i);
		}
		i++;
	}
}
