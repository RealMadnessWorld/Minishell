#include "../../includes/minishell.h"

static int	check_end(char *str, char aspas, int *quote_count, int *i)
{
	(*i)++;
	(*quote_count)++;
	while (str[*i] != aspas && str[*i])
	{
		if (str[(*i) + 1] == '\0')
			return (1);
		(*i)++;
	}
	(*quote_count)++;
	return (0);
}

static int	check_quotes(char *str)
{
	int		quote_count;
	int		i;
	char	*tmp;

	quote_count = 0;
	i = -1;
	tmp = str;
	while (tmp[++i])
	{
		if (tmp[i] == '\'')
		{
			if (check_end(tmp, '\'', &quote_count, &i))
				return (1);
		}
		else if (tmp[i] == '"')
		{
			if (check_end(tmp, '"', &quote_count, &i))
				return (1);
		}
	}
	return (quote_count);
}

char	*allocate(char *str, int quotes, e_token *token)
{
	char	*newstr;

	if (str[0] == '\'' && str[ft_strlen(str) - 1] == '\'')
		*token = e_single_quotes;
	else if (str[0] == '"' && str[ft_strlen(str) - 1] == '"')
		*token = e_quotes;
	newstr = ft_calloc((ft_strlen(str) - quotes + 1), sizeof(char));
	if (!newstr)
	{
		printf ("failed to malloc\n");
		return (NULL);
	}
	return (newstr);
}

char	*clean_str(char *str, int quotes, e_token *token)
{
	int		i;
	int		j;
	char	*newstr;

	i = -1;
	j = 0;
	newstr = allocate(str, quotes, token);
	while (str[++i])
	{
		if (str[i] == '"')
		{
			while (str[++i] != '"')
				newstr[j++] = str[i];
			continue ;
		}
		if (str[i] == '\'')
		{
			while (str[++i] != '\'')
				newstr[j++] = str[i];
			continue ;
		}
		newstr[j++] = str[i];
	}
	return (newstr);
}

int	handle_quotes(t_tokens *tkn_lst)
{
	int			quotes;
	t_tokens	*curr;
	char		*new;

	curr = tkn_lst;
	new = NULL;
	while (curr)
	{
		quotes = check_quotes(curr->str);
		printf("passei\n");
		if (!quotes)
		{
			curr = curr->next;
			continue ;
		}
		else if (quotes == 1)
			return ((printf("error: open quotes\n")));
		else if (quotes > 1)
		{
			new = clean_str(curr->str, quotes, &curr->token);
			free(curr->str);
			curr->str = NULL;
			curr->str = new;
		}
		curr = curr->next;
	}
	return (0);
}

// int main(int ac, char **av)
// {
// 	t_tokens	*first = malloc(sizeof(t_tokens));
// 	t_tokens	*second = malloc(sizeof(t_tokens));
// 	t_tokens	*third = malloc(sizeof(t_tokens));
// 	t_tokens	*curr = first;
// 	int			i = 0;

// 	first->str = ft_strdup("\"hello \"hello\" hello\"");
// 	second->str = ft_strdup("\"\"hey \'I am \'cool\"\"");
// 	third->str = ft_strdup("\"\"aspas?\"\"");
// 	first->next = second;
// 	second->next = third;
// 	third->next = NULL;
// 	handle_quotes(first);
// 	while (curr)
// 	{
// 		printf("str\t%d = %s\n", i, curr->str);
// 		printf("token\t%d = %d\n", i,  curr->token);
// 		i++;
// 		curr = curr->next;
// 	}
// 	curr = first;
// 	while (curr)
// 	{
// 		free(curr->str);
// 		free(curr);
// 		curr = curr->next;
// 	}
// 	return (0);
// }
