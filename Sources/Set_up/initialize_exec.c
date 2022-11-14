
#include "../../includes/minishell.h"

t_exec	*initialize_exec(t_lex *lex)
{
	t_exec	*exec;
	int		i;

	i = 0;
	exec = ft_calloc(1, sizeof(t_exec));
	if (exec == NULL)
		errorexit("check initializiation of exec");
	exec->nbr_process = lex->no_processes;
	// if (envp[0] == NULL)
	// {
	// 	env->envp_bis = ft_calloc(3 + 1, sizeof(char *));
	// 	if (env->envp_bis == NULL)
	// 		errorexit("ALLOC ERROR");
	// 	env->envp_bis[0] = ft_strjoin("PWD=", getcwd(NULL, 0));
	// 	env->envp_bis[1] = ft_strdup("SHLVL=1");
	// 	env->envp_bis[2] = ft_strdup("_=/usr/bin/env");
	// 	env->envp_line = NULL;
	// 	env->envp_path = NULL;
	// }
	// else
	// {
	// 	env->envp_bis = envp;
	// 	env->envp_line = getenv("PATH");
	// 	env->envp_path = ft_split(env->envp_line, ':');
	// 	if (!env->envp_path)
	// 		errorexit("check initializiation of env->envp_path");
	// 	while (env->envp_path[i])
	// 	{
	// 		env->envp_path[i] = ft_strjoin(env->envp_path[i], "/");
	// 		if (!env->envp_path[i])
	// 			errorexit("env->envp_path[i] allocation fail");
	// 		i++;
	// 	}
	// }
	exec->end[0] = 0;
	exec->end[1] = 0;
	exec->buffer[0] = 0;
	exec->isheredoc = 0;
	return (exec);
}
