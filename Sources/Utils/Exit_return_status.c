#include "../../includes/minishell.h"

int	perror_return_msg(char *str, int status)
{
	perror(str);
	return (status);
}

void	perror_exit_status(char *arg, char *str, int status)
{
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	if (str)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	exit(status);
}

int	perror_return_status(char *arg, char *str, int status)
{
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	if (str)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	return (status);
}

int	perror_return_export_unset(char *arg, char *ex_or_unset, int status)
{
	ft_putstr_fd(ex_or_unset, 2);
	ft_putstr_fd(": '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (status);
}
