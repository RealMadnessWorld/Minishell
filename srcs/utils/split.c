#include "../../includes/minishell.h"

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
		if (str[i] == '"')
			quotes *= -1;
		if (str[i] == c && quotes == -1)
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
	int 		quote;

	i = x;
	j = 0;
	quote = -1;
	*tmp = malloc(sizeof(char) * ft_strlen(str) + 1);
	while (str[i])
	{
		if (str[i] == '"')
			quote *= -1;
		if (str[i] == c && quote != 1)
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

static void	copy_str(char const *str, char c, t_cmd *d)
{
	char *tmp;
	int i;

	i = 0;
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

void	split(char const *s, char c, t_cmd *d)
{
	if (!s)
		return ;
	d->cmdline = (char **)malloc(sizeof(char *) * (split_counter(s, c) * 2 - 1));
	copy_str(s, c, d);
}
