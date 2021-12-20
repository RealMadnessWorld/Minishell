#include "../../includes/minishell.h"

int	open_fd(t_data *d)
{
	if (d->fd.out_name)
	{
		d->fd.out = open(d->fd.out_name, O_WRONLY | O_CREAT, 0777);
		if (d->fd.out == -1)
			return 0;
		d->fd.out_original = dup(STDOUT_FILENO);
		dup2(d->fd.out, STDOUT_FILENO);
	}
	if (d->fd.in_name)
	{
		d->fd.in = open(d->fd.in_name, O_RDONLY);
		if (d->fd.in == -1)
			return 0;
		d->fd.in_original = dup(STDIN_FILENO);
		dup2(d->fd.in, STDIN_FILENO);
	}
	return 1;
}

// int	double_open(t_data *d)
// {
// 	if (d->fd.out_name)
// }