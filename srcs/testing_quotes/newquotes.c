#include "../../includes/minishell.h"

static int check_end(char *str, char aspas, int *quote_count, int *i)
{
	(*i)++;
	(*quote_count)++;
	while (str[*i] != aspas && str[*i])
	{
		if (str[(*i) + 1] == '\0')
			return (1);
		(*i)++;
	}
	//printf("str[%d]: %c\n", *i, str[*i]);
	(*quote_count)++;
	return (0);
}

static int	check_quotes(char **str)
{
	int	quote_count;
	int	i;
	char *tmp;

	quote_count = 0;
	i = -1;
	tmp = *str;
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

// int	check_command_ret_q_count(char *str, int echo)
// {
// 	int	i;
// 	int	count;

// 	i = -1;
// 	count = 0;
// 	while (str[++i] != ' ')
// 	{
// 		if (str[i] == '"' || str[i] == '\'')
// 			count++;
// 	}
// 	while (!(ft_isalnum(str[++i])) && str[i])
// 	{
// 		if (echo == 0 && str[i] == '-' && (str[i + 1] == 'n'))
// 		{
// 			i++;
// 			continue;
// 		}
// 		else if (str[i] == '"' || str[i] == '\'' && !(ft_isalnum(str[i + 1])))
// 			count++;
// 	}
// 	return (count);
// }

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

void	trim_quotes(char **str, char **newstr, char aspa, int *i, int *j)
{
	char	*tmp;
	char	*new;

	tmp = *str;
	new = *newstr;
	while (tmp[++(*i)] != aspa)
	{
		new[(*j)++] = tmp[*i];
	}
}

char	*clean_str(char **str, int quotes)
{
	int		i;
	int		j;
	char	*newstr;
	char	*tmp;

	tmp = *str;
	i = -1;
	j = 0;
	newstr = allocate(*str, quotes);
	while (tmp[++i])
	{
		if (tmp[i] == '"' || tmp[i] == '\'')
		{
			trim_quotes(str, &newstr, tmp[i], &i, &j);
			continue;
		}
		newstr[j++] = tmp[i];
	}
	return (newstr);
}

int	handle_quotes(char ***str)
{
	int		i;
	int		quotes;
	char	*curr;
	char	*new;

	i = -1;
	new = NULL;
	while (*str[++i])
	{
		curr = *str[i];
		quotes = check_quotes(str[i]);
		if (!quotes)
			continue;
		else if (quotes == 1)
			return ((printf("error: open quotes\n")));
		else if (quotes > 1)
		{
			free(curr);
			new = clean_str(str[i], quotes);
			*str[i] = new;
		}
	}
	return (0);
}

int main(int ac, char **av)
{
	char **dbl = malloc(sizeof(char *) * (2 + 1));
	char *mal;

	mal = ft_strdup("ec\'h\'o");
	dbl[0] = mal;
	dbl[1] = NULL;
	handle_quotes(&dbl);
	printf("str[0] = %s\n", dbl[0]);
}
