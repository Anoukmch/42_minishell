#include "../../includes/minishell.h"

int	executor(t_child **child, t_exec *exec, t_env *env, t_lex *lex)
{
	int	i;

	i = 0;
	if (get_heredoc(child, exec, env))
		return (1);
	while (child[i])
	{
		if (command_path(child[i], env))
			return (1);
		if (processes(child[i], exec, env, lex))
			return (1);
		i++;
	}
	close_piping(exec);
	return (0);
}
