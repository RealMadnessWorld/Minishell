#include "../../includes/minishell.h"

static long long	ft_stoi(char *str)
{
	long long	signal;
	long long	result;
	char		*p;

	p = (char *)str;
	signal = 1;
	result = 0;
	while (*p == ' ' || *p == '\t' || *p == '\n'
		|| *p == '\r' || *p == '\v' || *p == '\f')
		p++;
	if (*p == '+')
		p++;
	else if (*p == '-')
	{
		p++;
		signal = -1;
	}
	while (*p > 47 && *p < 58)
		result = result * 10 + *p++ - 48;
	result = result * signal;
	return (result);
}

static int	not_int(char *s)
{
	int			i;
	int			len;
	char		*tmp;
	long long	check_size;
	long long	max_int;

	i = 0;
	len = ft_strlen(s);
	tmp = s;
	check_size = ft_stoi(tmp);
	max_int = 2147483647;
	if (check_size > max_int)
		return (1);
	if (s[i] == '-' && ft_isdigit(s[1]))
		i++;
	while (i < len)
	{
		if (!(ft_isdigit(s[i++])))
			return (1);
	}
	return (0);
}

void	exit_func(t_data *d, t_tokens *t)
{
	int exit_nbr;

	exit_nbr = 0;
	if (d->cmd.str != NULL)
	{
		if (t->next)
		{
			if (t->next->str)
			{

				if (not_int((t->next->str)))
					exit_nbr = throw_error("exit", 255);
				else if (t->next->next)
				{
					g.g_status = throw_error("exit", 1);
					return ;
				}
				else if ((ft_atoi(t->next->str)) > 255)
					exit_nbr = (ft_atoi(t->next->str)) % 255;
				else
					exit_nbr = ft_atoi(t->next->str);
			}
		}
		clear_history();
	}
	everyone_be_freeee(d);
	printf(CLR_CYN"Bye daddy! Have a great day! 🖤🖤🖤\n"CLR_RST);
	exit(exit_nbr);
}

void	clear_paths(t_data *d)
{
	int i;

	i = -1;
	while (d->bin_paths[++i])
		free(d->bin_paths[i]);
	free(d->bin_paths);
	d->bin_paths = NULL;
}
