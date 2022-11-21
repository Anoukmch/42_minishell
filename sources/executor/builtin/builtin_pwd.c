#include "../../../includes/minishell.h"

int	command_pwd(void)
{
	char	*s;

	s = getcwd(NULL, 0);
	if (!s)
		return (1);
	ft_printf("%s\n", s);
	return (0);
}
