#include "../includes/minishell.h"

int	validate_export(t_tokens *com)
{

}

t_bool check_command(t_tokens *com)
{
	if (ft_strcmp("cd", com->str))
		if (validate_cd(com))
			return (1);
	if (ft_strcmp("pwd", com->str))
		if (validate_pwd(com))
			return (1);
	if (ft_strcmp("export", com->str))
		if (validate_export(com))
			return (1);
	if (ft_strcmp("unset", com->str))
		if (validate_unset(com))
			return (1);
	return (0);
}

t_bool	validate_tokens(t_tokens *tkn)
{
	t_tokens *curr;

	curr = tkn;
	while (curr)
	{
		if (curr->token == e_command)
			if (check_command(curr->token))
				return (1);
		curr = curr->next;
	}
	return (0);
}

// static void	parse_quotes(char **str, char c, t_data *data, int pos)
// {
// 	if (c = "'")
// 		str[i] = ft_str
// }

// void	check_quotes(char **str, t_data *data)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (str[i])
// 	{
// 		j = 0;
// 		while(str[i][j])
// 		{
// 			if (str[i] == "'" || str[i] == "\"")
// 				parse_quotes(str, str[i], data, i);
// 			j++;
// 		}
// 		i++;
// 	}
// }
