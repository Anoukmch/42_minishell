
#include "../../includes/minishell.h"

t_exec	*initialize_exec(t_lex *lex, char **envp)
{
	t_exec	*exec;
	int		i;

	i = 0;
	exec = ft_calloc(1, sizeof(t_exec));
	if (exec == NULL)
		errorexit("check initializiation of exec");
	exec->nbr_process = lex->no_processes;
	if (envp[0] == NULL)
	{
		exec->envp_bis = ft_calloc(3 + 1, sizeof(char *));
		if (exec->envp_bis == NULL)
			errorexit("ALLOC ERROR");
		exec->envp_bis[0] = ft_strjoin("PWD=", getcwd(NULL, 0));
		exec->envp_bis[1] = ft_strdup("SHLVL=1");
		exec->envp_bis[2] = ft_strdup("_=/usr/bin/env");
		exec->envp_line = NULL;
		exec->envp_path = NULL;
	}
	else
	{
		exec->envp_bis = envp;
		exec->envp_line = getenv("PATH");
		exec->envp_path = ft_split(exec->envp_line, ':');
		if (!exec->envp_path)
			errorexit("check initializiation of exec->envp_path");
		while (exec->envp_path[i])
		{
			exec->envp_path[i] = ft_strjoin(exec->envp_path[i], "/");
			if (!exec->envp_path[i])
				errorexit("exec->envp_path[i] allocation fail");
			i++;
		}
	}
	exec->end[0] = 0;
	exec->end[1] = 0;
	exec->buffer[0] = 0;
	exec->isheredoc = 0;
	return (exec);
}
