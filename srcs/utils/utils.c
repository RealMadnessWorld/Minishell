#include "../../includes/minishell.h"

void	do_env(char **envp)
{
    int i = 0;

	while (envp[i])
		printf("%s\n", envp[i++]);
}

void	add(t_tokens *old, char *new)
{
	free(old->str);
	old->str = NULL;
	old->str = new;
}

void	env_print(t_data *data)
{
	t_envars	*elist;

	elist = data->envars_list;
	while (elist)
	{
	printf("%s%s\n", elist->key, elist->value);
	elist = elist->next;
	}
}