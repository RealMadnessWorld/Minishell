#include "./includes/minishell.h"


t_envars	*qual_o_ultimo_mesmo(t_envars *t)
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

t_envars	*cria_um_novo(char *key, char *value)
{
	t_envars *novo;

	novo = (t_envars *)malloc(sizeof(t_envars));
	novo->key = key;
	novo->value = value;
	novo->next = NULL;
	return novo;
}

void	para_o_fim_puta(t_envars **t, t_envars *novo)
{
	t_envars *tmp;

	tmp = qual_o_ultimo_mesmo(*t);
	if (!*t)
	{
		*t = novo;
		return ;
	}
	tmp->next = novo;
}

int	compare_sizes(char *s1, char *s2)
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

void	envars_swap(t_envars **t)
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

void	order(t_envars *t)
{
	t_envars *tmp;

	tmp = t;
	while (!ordered(tmp))
	{
		if (compare_sizes(tmp->key, tmp->next->key) > 0)
		{
			swap(&tmp);
			return ;
		}
		if (tmp->next->next == NULL)
			return ;
		tmp = tmp->next;
	}
}

void	print(t_envars *t)
{
	int i = 0;
	while (t)
	{
		printf("node %i ... %s=%s\n",i,t->key,t->value);
		i++;
		t = t->next;
	}
}

static void	puta_que_pariu(t_envars *t)
{
	t_envars *tmp;

	para_o_fim_puta(&t, cria_um_novo("hoje", "teste"));
	para_o_fim_puta(&t, cria_um_novo("po caralho", "puta"));
	para_o_fim_puta(&t, cria_um_novo("fds esta", "merda"));
	para_o_fim_puta(&t, cria_um_novo("amanha", "alcool"));

	print(t);

	printf("\n------------------------------\n\n");
	while (!ordered(t))
		order(t);

	print(t);

	tmp  = t;
	while(t)
	{
		free(tmp);
		t = t->next;
		tmp = t;
	}
}

int	main(void)
{
	t_envars *t;

	t = NULL;
	puta_que_pariu(t);
	return 0;
}