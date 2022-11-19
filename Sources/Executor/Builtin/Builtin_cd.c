#include "../../../includes/minishell.h"

int	command_cd(t_child *child)
{
	if (child->parser_cmd[1] == NULL || !ft_strcmp(child->parser_cmd[1], "~"))
	{
		if (chdir(getenv("HOME")) != 0)
			return (perror_return_status(NULL, 1));
	}
	else
	{
		if (child->parser_cmd[1][0] != '\0' && chdir(child->parser_cmd[1]) != 0)
			return (perror_return_status(NULL, 1));
	}
	return (0);
}
