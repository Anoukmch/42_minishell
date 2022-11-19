#include "../../../includes/minishell.h"

int	processes(t_child *child, t_exec *exec, t_env *env, t_lex *lex)
{
	if (exec->nbr_process == 1 && child->isbuiltin == true)
	{
		if (single_builtin(child, exec, env, lex))
		{
			g_exit_code = 1;
			return (1);
		}
		else
			g_exit_code = 0;
	}
	else
	{
		if (child_exec(child, exec, env, lex))
			return (1);
	}
	return (0);
}
