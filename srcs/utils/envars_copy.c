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

t_envars	*env_last(t_envars *t)
{
	if (!t)
		return NULL;
	while(t)
	{
		if (t->next == NULL)
			return t;
		t = t->next;
	}
	return t;
}

t_envars	*env_new(char *key, char *value)
{
	t_envars *novo;

	novo = (t_envars *)malloc(sizeof(t_envars));
	novo->key = key;
	novo->value = value;
	novo->next = NULL;
	return novo;
}

void	env_add_lst(t_envars **t, t_envars *new)
{
	t_envars *tmp;

	tmp = env_last(*t);
	if (!*t)
	{
		*t = new;
		return ;
	}
	tmp->next = new;
}
