#include "minishell.h"

int	main(void)
{
	char	*str;
	char	**cml;
	int		i;

	cml = NULL;
	str = readline("What is your command?\t\n");
	i = split(str, ' ', cml);
	printf("hi\n");
	while(i > 0)
	{
		printf("%s\n", cml[i]);
		i--;
	}
	free(cml);
}