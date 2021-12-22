#include "../../includes/minishell.h"

static int	str_size(const char *str, char c)
{
	int	i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != c)
			count++;
		i++;
	}
	// printf("%i\n", count);
	return (count);
}

int	str_quotes_checker(int i, const char *str, int quotes)
{
	if (str[i] == '"' && quotes == 0)
		return (1);
	else if (str[i] == '\'' && quotes == 0)
		return (2);
	else if (str[i] == '"' && quotes == 1)
		return (0);
	else if (str[i] == '\'' && quotes == 1)
		return (1);
	else if (str[i] == '"' && quotes == 2)
		return (2);
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
	quotes = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'')
			quotes = str_quotes_checker(i, str, quotes);
		if (str[i] == c && quotes == 0)
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
	quotes = 0;
	*tmp = malloc(sizeof(char) * str_size(str, c) + 1);
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			quotes = str_quotes_checker(i, str, quotes);
		if (str[i] == c && quotes == 0)
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
	char	*also_tmp;
	int		i;
	int		x;

	if (!str)
		return ;
	i = 0;
	x = (split_counter(str, c) * 2);
	d->cmdline = (char **)malloc(sizeof(char *) * x);
	while(str[i])
	{
		i = split_str(str, c, i, &tmp);
		also_tmp = tmp;
		tmp = ft_strtrim(tmp, " ");
		d->cmdline[d->i] = ft_strdup(tmp);
		d->i++;
		if (d->i != x - 1)
		{
			d->cmdline[d->i] = ft_strdup("|");
			d->i++;
		}
		free(also_tmp);
		free(tmp);
	}
	d->cmdline[d->i] = NULL;
}
