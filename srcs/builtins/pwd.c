#include "../../includes/minishell.h"

int	do_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 4096);
	if (pwd)
	{
		ft_putendl_fd(pwd, 1);
		free(pwd);
		pwd = NULL;
		return (0);
	}
	else
		return (1);
}
