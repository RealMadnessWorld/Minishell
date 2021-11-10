#include "../includes/minishell.h"

static int check_end(char *str, char aspas, int *quotes_exist, int *j)
{
	*quotes_exist = *quotes_exist++;
	while (str[*j] != aspas)
	{
		if (str[*j] == '\0')
			return (1);
		*j = *j++;
	}
	return (0);
}

static int	open_qs(char **str)
{
	int	quotes_exist;
	int	i;
	int	j;

	quotes_exist = 0;
	i = -1;
	while (str[++i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '\'')
			{
				if (check_end((str[i][j]), '\'', &quotes_exist, &j))
					return (1);
			}
			else if (str[i][j] == '"')
			{
				if (check_end((str[i][j]), '"', &quotes_exist, &j))
					return (1);
			}
			j++;
		}
	}
	return (quotes_exist);
}

int	q_find(char *str)
{
	int	i;

	i = 0;
	while (str[i] != ' ')
	{
		if (str[i] == "'" || str[i] == "'")
	}
}

int	trim_quotes(char **str)
{
	int	i;
	int	j;
	int	check_quotes;

	i = 0;
	j = 0;
	check_quotes = open_qs(str);
	if (check_quotes == 1)
		return ((printf("error: open quotes\n")));
	else if (!check_quotes)
		return (0);
	if (q_find(str[i]))
	{
		free(str[i]);

	while (str[i])
	{
		if (str[i] == echo)
		{
			j = 0;
			while (str[i][j])
			{
				if (str[i][j] == '"')
				{
					if (parse_dbquotes(str, &i))
						return (1);
				}
				else if (str[i][j] == "'")
				{
					if (parse_sgquotes(str, &i))
						return (1);
				}
				j++;
			}
			i++;
		}
	}
	return (0);
}



static int	parse_dbquotes(t_tokens	**tkn, int i)
// {
// 	// t_tokens	*curr;
// 	// char		*newstr;
// 	// t_bool		iter;
// 	// int			pos;

// 	// curr = *tkn;
// 	// iter = true;
// 	// pos = i + 1;
// 	// newstr = NULL;
// 	// while (iter && curr)
// 	// {
// 	// 	if (curr->str[pos] != '"')
// 	// 	{
// 	// 		newstr = append_char(newstr, check_q_count(curr));
// 	// 	}
// 	// }
// 	int i = 0;
// 	int x = 0;
// 	int j = 0;
// 	char *str;
// 	char *also_str;

// 	str = (*tkn)->str;
// 	also_str = (*tkn)->str;
// 	while(also_str[j] != '\0')
// 	{
// 		while(also_str[j] == '"')
// 		{
// 			j++;
// 			x++;
// 		}
// 		(*tkn)->str[i] = str[i + x];
// 		i++;
// 		j++;
// 	}
// 	(*tkn)->str[i] = '\0';
// }
