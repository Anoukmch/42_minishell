
#include "../../includes/minishell.h"

int	executort_child **child, t_exec *exec, t_env *env)
{
	int	i;

	i = 0;
	while (child[i])
	{
		if (command_path(child[i], env))
			perror_return("command not found");
		if (processes(child[i], exec, env))
			return (1);
		i++;
	}
	return (0);
}
