
#include "../../includes/minishell.h"

void    perror_exit_child(char *str)
{
    perror(str);
    exit(1);
}

int		perror_return(char *str)
{
    perror(str);
    return (1);
}

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
