#include "../../includes/minishell.h"

void	do_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 4096);
	ft_putendl_fd(pwd, 1);
	free(pwd);
	pwd = NULL;
}
