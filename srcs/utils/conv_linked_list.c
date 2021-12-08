#include "../../includes/minishell.h"

char	**conv_tokens(t_tokens *t)
{
	char	**str;
	int		i;

	i = 0;
	str = (char **)malloc(sizeof(char *) * token_lstsize(t) + 1);
	if (!str)
		return (0);
	while (t)
	{
		str[i] = ft_strdup(t->str);
		t = t->next;
		i++;
	}
	// str[i] = NULL;
	return (str);
}

char	**conv_env(t_envars *t)
{
	char	**str;
	int		i;

	i = 0;
	str = (char **)malloc(sizeof(char *) * env_lstsize(t) + 1);
	if (!str)
		return (0);
	while (t)
	{
		ft_strjoin(t->key, "=");
		str[i] = ft_strdup(ft_strjoin(t->key, t->value));
		t = t->next;
		i++;
	}
	i = 0;
	while (str[i])
	{
		printf("str[%i] = %s\n", i, str[i]);
		i++;
	}
	// str[i] = NULL;
	return (str);
}