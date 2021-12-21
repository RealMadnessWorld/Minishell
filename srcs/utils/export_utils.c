#include "../../includes/minishell.h"

static int	compare_sizes(char *s1, char *s2)
{
	int i = 0;
	int count;

	if (!s2)
		return (0);
	while (s1 && s1[i] == s2[i])
		i++;
	count = (unsigned char)s1[i] - (unsigned char)s2[i];
	if (s1[i] == '\0')
		return (-1);
	return (count);
}

int		ordered(t_envars *t)
{
	while (t)
	{
		if (t->next == NULL)
			return (1);
		if (compare_sizes(t->key, t->next->key) > 0)
			return (0);
		t = t->next;
	}
	return (1);
}

static void	envars_swap(t_envars **t)
{
	t_envars	**tmp;
	char		*key;
	char		*value;

	tmp = t;
	key = (*tmp)->key;
	value = (*tmp)->value;
	(*tmp)->key = (*tmp)->next->key;
	(*tmp)->value = (*tmp)->next->value;
	(*tmp)->next->key = key;
	(*tmp)->next->value = value;
}

void	print_export(t_envars *t)
{
	t_envars	*curr;

	curr = t;
	while (curr)
	{
		printf("declare -x %s", curr->key);
		if (curr->value)
			printf("=\"%s\"\n", curr->value);
		else
			printf("\n");
		curr = curr->next;
	}
}

void	order(t_envars *t)
{
	t_envars *tmp;

	tmp = t;
	while (!ordered(tmp))
	{
		if (compare_sizes(tmp->key, tmp->next->key) > 0)
		{
			envars_swap(&tmp);
			return ;
		}
		if (tmp->next->next == NULL)
			return ;
		tmp = tmp->next;
	}
}
