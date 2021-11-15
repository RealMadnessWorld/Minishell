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

char	*allocate(char *str, int quotes)
{
	char	*newstr;

	if (str[0] == '\'' && str[ft_strlen(str)] == '\'')
		newstr = ft_strtrim(str, "'");
	else if (str[0] == '"' && str[ft_strlen(str)] == '"')
		newstr = ft_strtrim(str, "\"");
	else
		newstr = ft_calloc((ft_strlen(str) - quotes + 1), sizeof(char));
	if (!newstr)
	{
		printf ("failed to malloc\n");
		return (NULL);
	}
	return (newstr);
}

char	*clean_str(char *str, int quotes)
{
	int		i;
	int		j;
	char	*newstr;

	i = -1;
	j = 0;
	newstr = allocate(str, quotes);
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

int	handle_quotes(char **str)
{
	int		quotes;
	char	*curr;
	char	*new;
	char	**dbl;

	new = NULL;
	dbl = str;
	while (*dbl)
	{
		curr = *dbl;
		quotes = check_quotes(*dbl);
		if (!quotes)
			continue ;
		else if (quotes == 1)
			return ((printf("error: open quotes\n")));
		else if (quotes > 1)
		{
			new = clean_str(*dbl, quotes);
			free(curr);
			curr = NULL;
			*dbl = new;
		}
		dbl++;
	}
	return (0);
}

// int main(int ac, char **av)
// {
// 	char	**dbl = malloc(sizeof(char *) * 3);
// 	char	*mal;
// 	char	*sec;
// 	char	**fre = dbl;

// 	mal = ft_strdup("ec\'h\'o");
// 	sec = ft_strdup("hey \"I ' am'' \" cool");
// 	dbl[0] = mal;
// 	dbl[1] = sec;
// 	dbl[2] = 0;
// 	handle_quotes(dbl);
// 	printf("str[0] = %s\n", *dbl);
// 	dbl++;
// 	printf("str[1] = %s\n", *dbl);
// 	while (*fre)
// 	{
// 		free(*fre);
// 		fre++;
// 	}
// 	return (0);
// }
