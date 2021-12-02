#include "../../includes/minishell.h"

void	export_func(t_data *d, t_tokens *t)
{
	t_tokens	*curr;

	curr = t->next;
	do_export(d->envars_list, t->str);
	while (curr->next && curr->next->token != e_pipe)
	{
		do_export(d->envars_list, t->str);
		curr = curr->next;
	}
}

void	do_export(t_envars *lst, char *to_add)
{
	t_envars	*curr;
	t_envars	*prev;
	char		**new;

	curr = lst;
	prev = curr;
	if (!to_add)
	{
		do_env(lst);
		return ;
	}
	new = set_line(to_add);
	while (curr)
	{
		if (!(ft_strcmp(curr->key, new[0])))
		{
			if (curr->value)
				free(curr->value);
			curr->value = new[1];
			free(new[0]);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
	prev->next = add_node(new);
}

void	parse_envars(t_tokens *tkn_lst, t_envars *envars_lst)
{
	t_tokens	*curr;
	int			i;

	curr = tkn_lst;
	i = 0;
	while (curr)
	{
		if (curr->token == e_var)
		{
			while (curr->str[i++])
			{
				if (curr->str[i] == '=')
					do_export(envars_lst, curr->str);
			}
		}
		i = 0;
		curr = curr->next;
	}
}

// int main(int ac, char **av, char **envp)
// {
// 	t_data		*data;
// 	int			i = 1;
// 	t_tokens	*first = malloc(sizeof(t_tokens));

// 	data = malloc(sizeof(t_data));
// 	data->envars_list = set_envars_list(envp);
// 	first->str = ft_strdup("testing=working");
// 	first->token = e_var;
// 	parse_envars(first, data->envars_list);
// 	do_env(data->envars_list);
// 	return (0);
// }
