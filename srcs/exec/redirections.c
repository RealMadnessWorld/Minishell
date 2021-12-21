#include "../../includes/minishell.h"

int	handle_fd(t_data *d, t_tokens *t)
{
	set_fd_names(d, t);
	if (!open_fd(d))
	{
		ft_putstr_fd("caralho\n", 2);
		printf("bro, idk what happened BUTT I cant find that file...\n");
		printf("maybe you have virtual 🐀 in your computer?\n");
		restart_fd(d);
		return (0);
	}
	// ft_putstr_fd("putas\n", 2);
	d->fd.weirdoc = 0;
	d->fd.append = 0;
	return (1);
}

int	open_fd(t_data *d)
{
	if (d->fd.out_name)
		return (choose_out(d));
	if (d->fd.in_name)
		return (choose_in(d));
	return (1);
}

int	choose_out(t_data *d)
{
	if (d->fd.append == 0)
	{
		d->fd.out = open(d->fd.out_name, O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (d->fd.out == -1)
			return (0);
		d->fd.out_original = dup(STDOUT_FILENO);
		dup2(d->fd.out, 1);
		ft_putstr_fd("putas\n", 2);
	}
	if (d->fd.append == 1)
	{
		d->fd.out = open(d->fd.out_name, O_WRONLY | O_APPEND | O_CREAT, 0777);
		if (d->fd.out == -1)
			return (0);
		d->fd.out_original = dup(STDOUT_FILENO);
		dup2(d->fd.out, STDOUT_FILENO);
	}
	return (1);
}

int	choose_in(t_data *d)
{
	if (d->fd.weirdoc == 0)
	{
		d->fd.in = open(d->fd.in_name, O_RDONLY);
		if (d->fd.in == -1)
			return (0);
		d->fd.in_original = dup(STDIN_FILENO);
		dup2(d->fd.in, STDIN_FILENO);
	}
	if (d->fd.weirdoc == 0)
	{
		d->fd.in = open(".heredoc", O_RDONLY);
		if (d->fd.in == -1)
			return (0);
		d->fd.in_original = dup(STDIN_FILENO);
		dup2(d->fd.in, STDIN_FILENO);
	}
	return (1);
}

void	close_start_fd(t_data *d)
{
	if (d->fd.in_name != NULL)
	{
		free(d->fd.in_name);
		dup2(d->fd.in_original, 0);
		close(d->fd.in_original);
		close(d->fd.in);
		d->fd.in_name = NULL;
		d->fd.in = -1;
		d->fd.in_original = -1;
	}
	if (d->fd.out_name)
	{
		free(d->fd.out_name);
		dup2(d->fd.out_original, 1);
		close(d->fd.out_original);
		close(d->fd.out);
		d->fd.out_name = NULL;
		d->fd.out = -1;
		d->fd.out_original = -1;
	}
}
