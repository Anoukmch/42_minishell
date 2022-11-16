#include "../../includes/minishell.h"

int	g_exit_code = 0;

void	initialize_struct(t_child	***child, t_exec **exec, t_lex *lex)
{
	*child = initialize_child(lex);
	*exec = initialize_exec(lex);
	if (!(*child) || !(*exec))
	{
		free_struct(*child, *exec);
		perror("Check initalization structures");
		exit (1);
	}
}

int	main(int ac, char **ag, char **envp)
{
	t_lex	*lex;
	t_child	**child;
	t_exec	*exec;
	t_env	*env;

	if (ac != 1 || !ag[0])
		return (perror_return("Wrong number of argument"));
	signal(SIGQUIT, SIG_IGN);
	env = initialize_env(envp);
	if (!env)
		return (perror_return("Check initalization structures"));
	while (1)
	{
		handle_signals();
		lex = initialize_lex();
		if (lex)
		{
			if (!check_syntax(lex)) /* where is the parser and initialize ? */
			{
				add_history(lex->line);
				initialize_struct(&child, &exec, lex);
				if (!parser(lex, child, env))
				{
					if (!executor(child, exec, env))
						close_piping(exec);
				}
				waitpid(exec->last_pid, &g_exit_code, 0);
				// while (wait(&tmp) > 0)
				// 	continue ;
				// if (WIFEXITED(tmp))
				// 	main_truct.g_exit_code = WEXITSTATUS(tmp); /* WEXITSTATUS(child_info) = $? */
				free_struct(child, exec);
				free_lex(lex);
			}
		}
		else
			exit(g_exit_code);
	}
	free_env(env);
	return (0);
}

// waitpid(exec->last_pid, &errno, 0);
// 				while (wait(NULL) > 0)
// 					continue ;
// 				if (WIFEXITED(errno))
// 					printf("%d\n", WEXITSTATUS(errno)); /* WEXITSTATUS(child_info) = $? */
