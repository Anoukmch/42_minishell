#include "../../includes/minishell.h"

void	perror_exit_status(char *str, int status)
{
	perror(str);
	exit(status);
}

int	perror_return_status(char *str, int status)
{
	perror(str);
	return (status);
}
