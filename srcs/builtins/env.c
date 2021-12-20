#include "../../includes/minishell.h"

int	do_env(t_envars *lst)
{
	t_envars	*elist;
	elist = lst;

	while (elist)
	{
		printf("%s=%s\n", elist->key, elist->value);
		elist = elist->next;
	}
	return (0);
}

// int main(int ac, char **av, char **envp)
// {
// 	t_data		*data;
// 	int			i = 1;

// 	data = malloc(sizeof(t_data));
// 	data->envars_list = set_envars_list(envp);
// 	// do_pwd(data->envars_list);
// 	// do_env(data->envars_list);
// 	// printf("-----\t-----\t-----\t-----\t-----\t-----\t-----\t-----\t-----\n");
// 	do_export(data->envars_list, "testing=working");
// 	do_env(data->envars_list);
// 	printf("11111\t11111\t11111\t11111\t11111\t11111\t11111\t11111\t11111\n");
// 	do_export(data->envars_list, "testing=REPLACEZEZEZEZE");
// 	do_env(data->envars_list);
// 	printf("22222\t22222\t22222\t22222\t22222\t22222\t22222\t22222\t22222\n");
// 	do_unset(&(data->envars_list), "testing");
// 	do_unset(&(data->envars_list), "GJS_DEBUG_TOPICS");
// 	// do_unset(&(data->envars_list), "SHELL");
// 	do_export(data->envars_list, NULL);

// 	return (0);
// }
