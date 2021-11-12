#include "../../includes/minishell.h"

static int check_end(char *str, char aspas, int *quotes_exist, int *j)
{
	*quotes_exist = 2;
	while (str[*j] != aspas && str[*j])
	{
		if (str[(*j) + 1] == '\0')
			return (1);
		*j = *j + 1;
	}
	return (0);
}

static int	check_ifopen_ret_1_if_qs(char *str)
{
	int	quotes_exist;
	int	i;

	quotes_exist = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			if (check_end(&(str[i]), '\'', &quotes_exist, &i))
				return (1);
		}
		else if (str[i] == '"')
		{
			if (check_end(&(str[i]), '"', &quotes_exist, &i))
				return (1);
		}
	}
	return (quotes_exist);
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
	while (!(ft_isalnum(str[++i])) && str[i])
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
		check_quotes = check_ifopen_ret_1_if_qs(str[i]);
		if (check_quotes == 1)
			return ((printf("error: open quotes\n")));
		else if (!check_quotes)
			continue;
		is_echo = ft_strncmp(str[i], "echo", 4);
		quotes_nbr = check_command_ret_q_count(str[i], is_echo);
		if (quotes_nbr)
		{
			free(str[i]);
			str[i] = clean_command_line(str[i], is_echo, quotes_nbr);
		}
	}
	return (0);
}

int main(int ac, char **av)
{
	char **dbl = malloc(sizeof(char *) * 2);
	char *mal = malloc(sizeof(char) * (ft_strlen("ec\'ch\'s") + 1));
	mal = "ec\'ch\'s";
	dbl[0] = mal;
	dbl[1] = NULL;
	trim_quotes(dbl);
}



(echo) (-n) ("ola' .'") | (e'ch'o) (-n) ("ola' .'")

ls > file | grep .c | wc -l
