#include "../../includes/minishell.h"

int	handle_fd(t_data *d, t_tokens *t)
{
	set_fd_names(d, t);
	if (!open_fd(d))
	{
		printf("bro, idk what happened BUTT I cant find that file...\n");
		printf("maybe you have virtual 🐀 in your computer?\n");
		return (0);
	}
	return (1);
}

int	open_fd(t_data *d)
{
	if (d->fd.out_name)
	{
		d->fd.out = open(d->fd.out_name, O_WRONLY | O_TRUNC | O_CREAT, 0777);
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

static int	its_redir(t_tokens *t)
{
	t_tokens *tmp;

	tmp = t;

	while (tmp && tmp->token != e_pipe)
	{
		if (tmp->token == e_smaller || tmp->token == e_bigger ||
			tmp->token == e_double_bigger)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

// static int	count_allocs(t_data *d, char **cmd, int *s, int *e)
// {
// 	int		i;
// 	char	*tmp;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	tmp = *cmd;
// 	while (tmp[i++])
// 	{
// 		if (tmp[i] == '<' || tmp[i] == '>' ||
// 			(tmp[i] == '>' && tmp[i + 1] == '>'))
// 			{
// 				(*s) = i;
// 				j = i++;
// 				while (ft_strcmp(tmp[j], d->fd.out_name))
// 					j++;
// 				(*e) = j++;
// 				i = j;
// 				while (tmp[i])
// 					i++;
// 			}
// 	}
// 	return (i);
// }

// static char	**trim_redir(t_data *d, char **cmd)
// {
// 	int		s;
// 	int		e;
// 	int		i;
// 	char	**newcmd;
// 	char	*str;

// 	s = 0;
// 	e = 0;
// 	i = count_allocs(d, cmd, &s, &e);
// 	newcmd = malloc(sizeof(char *) * (i + 1));
// 	str = *newcmd;
// 	i = -1;
// 	while ((*cmd)[++i])
// 	{
// 		if (i < s || i > e)
// 			(str)++ = ft_strdup((*cmd)[i]);
// 		free((*cmd)[i]);
// 		free(cmd[i]);
// 		cmd[i] = NULL;
// 		i++;
// 	}
// 	return (&newcmd);
// }

static void trim_redir(char **cmd)
{
    int i;

    i = 0;
    while(cmd[i])
    {
        if (*cmd[i] == '<' || *cmd[i] == '>')
        {
            while(cmd[i])
            {
                free(cmd[i]);
                cmd[i] = NULL;
                i++;
            }
            free(cmd[i]);
            cmd[i] = NULL;
            return ;
        }
        i++;
    }
}

void	execve_handler(t_data *d, t_tokens *t)
{
	t_exec	*x;
	//start_fd

	x = check_cmd(d, t);
	if (x == NULL)
		exit(throw_error(t->str, 127));
	if (its_redir(x->t))
	{
		if (!handle_fd(d, t))
			return (0);
		trim_redir(x->t);
		execve(x->path, x->t, x->env);
	}
	execve(x->path, x->t, x->env);
}
