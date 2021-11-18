#include "../../includes/minishell.h"

void	do_env(t_envars *lst)
{
	t_envars	*elist;
	elist = lst;

	while (elist)
	{
		printf("%s%s\n", elist->key, elist->value);
		elist = elist->next;
	}
}

int main(int ac, char **av, char **envp)
{
	t_data		*data;
	int			i = 0;

	data = malloc(sizeof(t_data));
	data->envars_list = set_envars_list(envp);
	// do_pwd(data->envars_list);
	do_env(data->envars_list);
	printf("-----\t-----\t-----\t-----\t-----\t-----\n");
	do_export(data->envars_list, "testing=working");
	do_env(data->envars_list);
	printf("-----\t-----\t-----\t-----\t-----\t-----\n");
	do_unset(data->envars_list, "testing");
	do_unset(data->envars_list, "LANG");
	do_unset(data->envars_list, "TERM_PROGRAM");
	do_export(data->envars_list, NULL);
	// exit_func(data);

	return (0);
}
