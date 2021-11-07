#include "../includes/minishell.h"

int	is_command(t_tokens *t)
{
	if (strcmp(t->str, "cd") == 0)
		return (1);
	if (strcmp(t->str, "echo") == 0)
		return (1);
	if (strcmp(t->str, "pwd") == 0)
		return (1);
	if (strcmp(t->str, "export") == 0)
		return (1);
	if (strcmp(t->str, "unset") == 0)
		return (1);
	if (strcmp(t->str, "env") == 0)
		return (1);
	if (strcmp(t->str, "exit") == 0)
		return (1);
	else
		return (0);
}