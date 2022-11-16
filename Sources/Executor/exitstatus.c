
#include "../../includes/minishell.h"

void    perror_exit_child(char *str)
{
    perror(str);
    exit(1);
}

int    perror_return(char *str)
{
    perror(str);
	return (1);
}

int    perror_return_zero(char *str)
{
    perror(str);
	return (0);
}

// void	exit_status(t_child **child)
// {
	// int i;
	// int k;
	// int j;

	// i = 1;
	// k = 1;
	// j = 0;
	// if (!child[k])
	// 	return ;
	// while (child[k]->parser_cmd[i])
	// {
	// 	if (!ft_strcmp(child[k]->parser_cmd[i], "$?"))
	// 	{
	// 		free(child[k]->parser_cmd[i]);
	// 		child[k]->parser_cmd[i] = ft_substr(exit_string, 0, ft_strlen(exit_string));

	// 	}
	// 	i++;
	// }
// }

