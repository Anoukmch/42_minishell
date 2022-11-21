#include "../../includes/minishell.h"

int	check_builtins_other(t_child *child)
{
	if (ft_strncmp("echo", child->parser_cmd[0], 5) == 0)
	{
		child->command = ft_strdup("echo");
		if (!child->command)
			return (1);
	}
	else if (ft_strncmp("cd", child->parser_cmd[0], 3) == 0)
	{
		child->command = ft_strdup("cd");
		if (!child->command)
			return (1);
	}
	else if (ft_strncmp("pwd", child->parser_cmd[0], 4) == 0)
	{
		child->command = ft_strdup("pwd");
		if (!child->command)
			return (1);
	}
	else if (ft_strncmp("exit", child->parser_cmd[0], 5) == 0)
	{
		child->command = ft_strdup("exit");
		if (!child->command)
			return (1);
	}
	return (0);
}

int	check_builtins_env(t_child *child)
{
	if (ft_strncmp("export", child->parser_cmd[0], 7) == 0)
	{
		child->command = ft_strdup("export");
		if (!child->command)
			return (1);
	}
	else if (ft_strncmp("unset", child->parser_cmd[0], 6) == 0)
	{
		child->command = ft_strdup("unset");
		if (!child->command)
			return (1);
	}
	else if (ft_strncmp("env", child->parser_cmd[0], 4) == 0)
	{
		child->command = ft_strdup("env");
		if (!child->command)
			return (1);
	}
	return (0);
}
