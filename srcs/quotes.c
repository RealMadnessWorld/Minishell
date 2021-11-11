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

static int	check_ifopen_ret_qs(char **str)
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

int	not_arg(char *str, int i, int echo)
{
	int	j;

	if (echo == 0)
	{

	}
	else
	{
		while (ft_isalnum(str[++i]))

	}
	return (0);
}

int	check_command_ret_q_count(char *str, int echo)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i] != ' ')
	{
		if (str[i] == '"' || str[i] == '\'')
			count++;
	}
	while (!(ft_isalnum(str[++i])))
	{
		if (echo == 0 && str[i] == '-' && (str[i + 1] == 'n'))
		{
			i++;
			continue;
		}
		else if (str[i] == '"' || str[i] == '\'' && !(ft_isalnum(str[i + 1])))
			count++;
	}
	return (count);
}

char	*clean_command_line(char *str, int echo, int quotes)
{
	char	*newstr;
	int		i;
	int		j;

	newstr = malloc((sizeof(char) * ft_strlen(str)) - quotes + 1);
	if (!newstr)
	{
		printf ("failed to malloc\n");
		return (NULL);
	}
	i = -1;
	j = 0;

	while (str[++i] != ' ')
	{
		if (str[i] != '"' || str[i] != '\'')
			newstr[j++] = str[i];
	}
	while (str[i] != '"' || str[i] != '\'' || str[i] == ' ')
	{
		if (str[i] == ' ' && echo == 0 && str[i - 1] == 'n' &&
		str[i - 2] == '-')
		i++;
	}
	while (str[i++])
		newstr[j++] = str[i];
	newstr[++j] = '\0';
	return (newstr);
}

int	trim_quotes(char **str)
{
	int	i;
	int	check_quotes;
	int	is_echo;
	int	quotes_nbr;

	i = -1;
	is_echo = 1;
	while (str[++i])
	{
		check_quotes = check_ifopen_ret_qs(str[i]);
		if (check_quotes == 1)
			return ((printf("error: open quotes\n")));
		else if (!check_quotes)
			continue;
		is_echo = ft_strncmp(str, "echo", 4);
		quotes_nbr = check_command_ret_q_count(str[i], is_echo);
		if (quotes_nbr)
		{
			free(str[i]);
			str[i] = clean_command_line(str[i], is_echo, quotes_nbr);
		}
	}
	return (0);
}
