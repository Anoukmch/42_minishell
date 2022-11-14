
#include "../../includes/minishell.h"

int	executor(t_lex *lex, t_child **child, t_exec *exec, t_env *env)
{
	int	i;

	i = 0;
    if (command_path(lex, child, env))
		return(perror_return("command not found"));
	while (child[i])
	{
		if (processes(child[i], exec, env))
			return (1);
		i++;
	}
	return (0);
}
