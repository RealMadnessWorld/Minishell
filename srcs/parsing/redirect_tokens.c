#include "../../includes/minishell.h"

// void	set_fd_str(t_data *d, char *str)
// {
// 	if (ft_strcmp("<", d->fd.curr_red) == 0)
// 	{
// 		check_fd_already_redin(d);
// 		if (!d->fd.curr_name)
// 		{
// 			printf("Where is the file you beautiful bastard?\n");
// 			return ;
// 		}
// 		else
// 			d->fd.in_name = ft_strdup(str);
// 	}
// 	else if (ft_strcmp(">", d->fd.curr_red) == 0)
// 	{
// 		check_fd_already_redout(d);
// 		if (!d->fd.curr_name)
// 		{
// 			printf("Where is the file you beautiful bastard?\n");
// 			return ;
// 		}
// 		d->fd.out_name = ft_strdup(str);
// 	}
// }

void	set_fd_names(t_data *d, t_tokens *t)
{
	t_tokens *l;
	t_tokens *tmp;

	tmp = t;
	l = t;
	while (tmp)
	{
		if (tmp->token == e_smaller)
		{
			check_fd_already_redin(d);
			if (!tmp->next)
			{
				printf("Where is the file you beautiful bastard?\n");
				return ;
			}
			d->fd.in_name = ft_strdup(tmp->next->str);
			tmp->next->token = e_fd;
			delete_redirection(&l);
			tmp = l;
		}
		else if (tmp->token == e_bigger || tmp->token == e_double_bigger)
		{
			check_fd_already_redout(d);
			if (!tmp->next)
			{
				printf("Where is the file you beautiful bastard?\n");
				return ;
			}
			d->fd.out_name = ft_strdup(tmp->next->str);
			tmp->next->token = e_fd;
			delete_redirection(&l);
			tmp = l;
		}
		if (tmp->next)
		{
			if (tmp->next == NULL)
				return ;
		}
		tmp = tmp->next;
	}
}

void	delete_util(t_tokens **t)
{
	t_tokens *tmp;

	tmp = *t;
	free(tmp->str);
	free(tmp->next->str);
	free(tmp->next);
	free(tmp);
	tmp = NULL;
}

void	delete_redirection(t_tokens **t)
{
	t_tokens *tmp;
	t_tokens *list;

	tmp = *t;
	if (tmp->token == e_smaller || tmp->token == e_bigger || tmp->token == e_double_bigger)
	{
		list = tmp->next->next->next;
		tmp->str = list->str;
		tmp->token = list->token;
		tmp->next = list->next;
		free(list);
		return ;
	}
	list = *t;
	if (tmp->next)
		tmp = list->next;
	while (list)
	{
		if (tmp->token == e_smaller || tmp->token == e_bigger || tmp->token == e_double_bigger)
		{
			if (!tmp->next->next)
			{
				delete_util(&tmp);
				list->next = NULL;
				return ;
			}
			else
				list->next = list->next->next->next;
			delete_util(&tmp);
			return ;
		}

		list = list->next;
	}
}

int	check_fd_already_redin(t_data *d)
{
	if (d->fd.i_in != 0)
	{
		d->fd.in = open(d->fd.in_name, O_WRONLY | O_CREAT, 0777);
		if (d->fd.in == -1)
		{
			printf("couldn't open that fila mate... sorry (not really)\n");
			return (0);
		}
		close(d->fd.in);
	}
	d->fd.i_in++;
	return (1);
}

int	check_fd_already_redout(t_data *d)
{
	if (d->fd.i_out != 0)
	{
		d->fd.out = open(d->fd.out_name, O_WRONLY | O_CREAT, 0777);
		if (d->fd.in == -1)
		{
			printf("couldn't open that fila mate... sorry (not really)\n");
			return (0);
		}
		close(d->fd.out);
	}
	d->fd.i_out++;
	return (1);
}

void	restart_fd(t_data *d)
{
	if (d->fd.in_name != NULL)
	{
		free(d->fd.in_name);
		dup2(d->fd.in_original, 0);
		close(d->fd.in_original);
		close(d->fd.in);
		d->fd.in_name = NULL;
		d->fd.in_original = -1;
		d->fd.in_original = -1;
	}
	if (d->fd.out_name)
	{
		free(d->fd.out_name);
		dup2(d->fd.out_original, 1);
		close(d->fd.out_original);
		close(d->fd.out);
		d->fd.out_name = NULL;
		d->fd.out_original = -1;
		d->fd.out_original = -1;
	}
}
