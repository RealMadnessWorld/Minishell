#include "../includes/minishell.h"

int	is_command(char *str)
{
	if (strcmp(str, "cd") == 0)
		return (1);
	if (strcmp(str, "echo") == 0)
		return (1);
	if (strcmp(str, "pwd") == 0)
		return (1);
	if (strcmp(str, "export") == 0)
		return (1);
	if (strcmp(str, "unset") == 0)
		return (1);
	if (strcmp(str, "env") == 0)
		return (1);
	if (strcmp(str, "exit") == 0)
		return (1);
	else
		return (0);
}

int	is_symbol()