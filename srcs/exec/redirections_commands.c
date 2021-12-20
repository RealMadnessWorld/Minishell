#include "../../includes/minishell.h"

int	do_red_smaller(t_data *d, t_tokens *tmp)
{
	check_fd_already_redin(d);
	if (!tmp->next)
	{
		printf("Where is the file you beautiful bastard?\n");
		return (0);
	}
	d->fd.in_name = ft_strdup(tmp->next->str);
	tmp->next->token = e_fd;
	d->fd.weirdoc = 0;
	return (1);
}

int	do_red_bigger(t_data *d, t_tokens *tmp)
{
	check_fd_already_redout(d);
	if (!tmp->next)
	{
		printf("Where is the file you beautiful bastard?\n");
		return (0);
	}
	d->fd.out_name = ft_strdup(tmp->next->str);
	tmp->next->token = e_fd;
	d->fd.append = 0;
	return (1);
}

int	do_red_weirdoc(t_data *d, t_tokens *tmp)
{
	char	*str;

	d->fd.out_original = dup(STDOUT_FILENO);
	d->fd.heredoc_fd = open(".heredoc", O_RDWR | O_TRUNC | O_APPEND | O_CREAT, 0777);
	if (d->fd.heredoc_fd == -1)
		return (0);
	str = readline(">");
	if (ft_strcmp(tmp->next->str, str) == 0)
		free(str);
	else
	{
		while (1)
		{
			str = readline("> ");
			write(d->fd.heredoc_fd, str, strlen(str));
			write(d->fd.heredoc_fd, "\n", 1);
			if (ft_strcmp(tmp->next->str, str) == 0)
			{
				free(str);
				d->fd.weirdoc = 1;
				return (1);
			}
			free(str);
		}
	}
	d->fd.weirdoc = 1;
	close(d->fd.heredoc_fd);
	return (1);
}

int	do_red_append(t_data *d, t_tokens *tmp)
{
	check_fd_already_append(d);
	if (!tmp->next)
	{
		printf("Where is the file you beautiful bastard?\n");
		return (0);
	}
	d->fd.out_name = ft_strdup(tmp->next->str);
	tmp->next->token = e_fd;
	d->fd.append = 1;
	return (1);
}