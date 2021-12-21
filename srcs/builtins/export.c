#include "../../includes/minishell.h"

t_envars	*copy_envars(t_envars *t)
{
	t_envars *copy;

	copy = NULL;
	while (t)
	{
		env_add_lst(&copy, env_new(t->key, t->value));
		t = t->next;
	}
	return (copy);
}

static int	empty_export(t_envars *lst)
{
	t_envars	*copy;

	copy = copy_envars(lst);
	while (!ordered(copy))
		order(copy);
	print_export(copy);
	free(copy);
	copy = NULL;
	return (0);
}

int exp_keyvalue(t_envars *lst, char **new)
{
	t_envars	*curr;
	t_envars	*prev;

	curr = lst;
	prev = curr;
	while (curr)
	{
		if (!(ft_strcmp(curr->key, new[0])) && new[1])
		{
			if (curr->value)
				free(curr->value);
			curr->value = new[1];
			free(new[0]);
			return (0);
		}
		else if (!(ft_strcmp(curr->key, new[0])) && new[1] == NULL)
			return (0);
		prev = curr;
		curr = curr->next;
	}
	prev->next = add_node(new);
	return (0);
}

int	do_export(t_envars *lst, char *to_add)
{
	char		**new;

	if (!to_add)
		return (empty_export(lst));
	if (!(ft_isalpha(*to_add)) && *to_add != '_')
		return(throw_error("export", 1));
	new = set_line(to_add);
	return (exp_keyvalue(lst, new));
}

int	export_func(t_envars *env, t_tokens *t)
{
	t_tokens	*curr;

	curr = t->next;
	if (do_export(env, curr->str))
		return (1);
	curr = curr->next;
	while (curr && curr->token != e_pipe)
	{
		if (do_export(env, curr->str))
			return (1);
		curr = curr->next;
	}
	return (0);
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
// 	int			i = 1;
// 	t_tokens	*first = malloc(sizeof(t_tokens));

// 	g_data = malloc(sizeof(t_data));
// 	g_data->envars_list = set_envars_list(envp);

// 	first->str = ft_strdup("testing=working");
// 	first->token = e_var;
// 	parse_envars(first, g_data->envars_list);
// 	do_export(g_data->envars_list, NULL);

// 	return (0);
// }
