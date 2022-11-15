
#include "../../includes/minishell.h"

int	executor(t_lex *lex, t_child **child, t_exec *exec, t_env *env)
{
	int	i;

	i = 0;
	while (child[i])
	{
		if (command_path(child[i], env))
			return(1);
		if (processes(child[i], exec, env))
			return (1);
		i++;
	}
	return (0);
}
