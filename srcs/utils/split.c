#include "../../includes/minishell.h"

int	str_quotes_checker(int i, const char *str, int quotes)
{
	if (str[i] == '\"' && quotes == 0)
		return (1);
	else if (str[i] == '\'' && quotes == 0)
		return (2);
	else if (str[i] == '\"' && quotes == 1)
		return (0);
	else if (str[i] == '\'' && quotes == 1)
		return (quotes);
	else if (str[i] == '\"' && quotes == 2)
		return (quotes);
	else
		return (0);
}

static int	split_counter(const char *str, char c)
{
	int	i;
	int	counter;
	int	quotes;

	if (!str)
		return (0);
	i = 0;
	counter = 1;
	quotes = -1;
	while (str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'')
			quotes = str_quotes_checker(i, str, quotes);
		if (str[i] == c && quotes > 0)
		{
			while (str[i] == c)
				i++;
			counter++;
		}
		i++;
	}
	return (counter);
}

static int	split_str(const char *str, char c, int x, char **tmp)
{
	static int	i;
	int			j;
	int 		quotes;

	i = x;
	j = 0;
	quotes = -1;
	*tmp = malloc(sizeof(char) * ft_strlen(str) + 1);
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			quotes = str_quotes_checker(i, str, quotes);
		if (str[i] == c && quotes > 0)
		{
			while (str[i] == c)
				i++;
			(*tmp)[j] = '\0';
			return (i);
		}
		(*tmp)[j] = str[i];
		i++;
		j++;
	}
	(*tmp)[j] = '\0';
	return (i);
}

void	split(char const *str, char c, t_cmd *d)
{
	char	*tmp;
	int		i;

	if (!str)
		return ;
	i = 0;
	d->cmdline = (char **)malloc(sizeof(char *) * (split_counter(str, c) * 2 - 1));
	while(str[i])
	{
		i = split_str(str, c, i, &tmp);
		tmp = ft_strtrim(tmp, " ");
		d->cmdline[d->i] = ft_strdup(tmp);
		d->i++;
		d->cmdline[d->i] = ft_strdup("|");
		d->i++;
		free(tmp);
	}
	d->cmdline[--d->i] = NULL;
}
