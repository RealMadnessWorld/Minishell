#include "../../includes/minishell.h"

int	open_fd(t_data *d)
{
	if (d->fd.out_name)
	{
		d->fd.out = open(d->fd.out_name, O_WRONLY | O_CREAT, 0777);
		if (d->fd.out == -1)
			return 0;
		d->fd.out_original = dup(STDOUT_FILENO);
		d->fd.out = dup2(d->fd.out, STDOUT_FILENO);
		close(d->fd.out);
	}
	if (d->fd.in_name)
	{
		d->fd.in = open(d->fd.in_name, O_RDONLY);
		if (d->fd.in == -1)
			return 0;
		d->fd.in_original = dup(STDIN_FILENO);
		d->fd.in = dup2(d->fd.in, STDIN_FILENO);
		close(d->fd.in);
	}
	return 1;
}