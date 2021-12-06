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

// void SortLinkedList()
// {
// 	t_envars	*node = NULL;
// 	t_envars	*temp = NULL;
// 	char		*tmpkey;
// 	char		*tmpvalue;

// 	node = g_data->envars_list;
// 	while(node != NULL)
// 	{
// 		temp = node;
// 		while (temp->next != NULL)
// 		{
// 			if(*temp->key > *temp->next->key)
// 			{
// 				tmpkey = temp->key;
// 				tmpvalue = temp->value;
// 				temp->key = temp->next->key;
// 				temp->value = temp->next->value;
// 				temp->next->key = tmpkey;
// 				temp->next->value = tmpvalue;
// 			}
// 			temp = temp->next;
// 		}
// 		node = node->next;
// 	}
// }

void	empty_export(void)
{
	t_envars	*lst;
	t_envars	*curr;
	t_envars	*curr_lowest;

	curr = g_data->envars_list;
	lst = g_data->envars_list;
	while (lst)
	{
		curr_lowest = curr;
		while (curr)
		{
			if (*curr->key < *curr_lowest->key)
				curr_lowest = curr;
			curr = curr->next;
		}
		printf("declare -x %s=\"%s\"\n", curr_lowest->key, curr_lowest->value);
		lst = lst->next;
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
		empty_export();
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

int main(int ac, char **av, char **envp)
{
	// int			i = 1;
	// t_tokens	*first = malloc(sizeof(t_tokens));

	// g_data = malloc(sizeof(t_data));
	// g_data->envars_list = set_envars_list(envp);

	// first->str = ft_strdup("testing=working");
	// first->token = e_var;
	// parse_envars(first, g_data->envars_list);
	// do_export(g_data->envars_list, NULL);
	char	*i = "Aviao";
	char	*b = "Bota";
	if (i > b)
		printf("yeah\n");
	return (0);
}
