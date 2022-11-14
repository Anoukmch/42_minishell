
#include "../../includes/minishell.h"

// void	check_env(t_exec *exec)
// {
// 	if (env->envp_bis == NULL)
// 	{
// 		env->envp_bis = ft_calloc(3 + 1, sizeof(char *));
// 		if (env->envp_bis == NULL)
// 			errorexit("ALLOC ERROR");
// 		env->envp_bis[0] = ft_strjoin("PWD=", getcwd(NULL, 0));
// 		env->envp_bis[1] = ft_strdup("SHLVL=1");
// 		env->envp_bis[2] = ft_strdup("_=/usr/bin/env");
// 	}
// }

void	executor(t_lex *lex, t_child **child, t_exec *exec, t_env *env)
{
	int	i;

	i = 0;
    if (command_path(lex, child, env) != 0)
	{
		ft_putstr_fd("cmd path not found\n", 2); /* or No such file or directory for unfind absolute command */
		return ;
		// return (1);
	}
	// check_env(exec);
	while (child[i])
	{
		processes(child[i], exec, env);
		i++;
	}
	// int z = 0;
	// while(env->envp_bis[z])
	// {
	// 	ft_printf("ENV: %s\n", env->envp_bis[z]);
	// 	z++;

	// }
	// return (0);
}
