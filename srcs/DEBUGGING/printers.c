#include "../../includes/minishell.h"

void printlst(t_tokens *also_tmp)
{
	t_tokens	*curr;
	int			i;

	i = 0;
	curr = also_tmp;
	while (curr)
	{
		printf(CLR_CYN"->\tnode [%i] %s\t\t\t token: %i\n"CLR_RST, i, curr->str, curr->token);
		curr = curr->next;
		i++;
	}
	printf("\n");
}

void	print_dbl(t_data data)
{
	int	i;

	i = 0;
	printf(CLR_RED"\n\n\t\t\tOUT OF SPLIT\n"CLR_RST);
	while (data.cmd.cmdline[i])
	{
		printf("str[%d] = %s\n", i, data.cmd.cmdline[i]);
		i++;
	}
	printf("\n\n");
}

// void	token_printer(t_tokens *also_tmp)
// {
// 	printf("\n\n----------------------------------------------\n----------------------------------------------\n\n");
// 	printf(CLR_RED"\t\t\tFULL LIST INFO\n"CLR_RST);
// 	printf("nmbr of nodes: %d\n", token_lstsize(also_tmp));
// 	printf("list strings:\n\n");
// 	printlst(also_tmp);
// 	printf(CLR_RED"\t\t\tLATEST NODE\n"CLR_RST);
// 	printf("str: %s\n", also_tmp->str);
// 	printf("token: %d\n\n", also_tmp->token);
// }

// printf(CLR_RED"\n\n\t\t\tOUT OF SPLIT\n"CLR_RST);
// while (data.cmd.cmdline[i])
// {
// 	printf("str[%d] = %s\n", i, data.cmd.cmdline[i]);
// 	i++;
// }
// printf("\n\n");
