#include "../../includes/minishell.h"

int	g_exit_code = 0;

void	initialize_struct(t_child	***child, t_exec **exec, t_lex *lex, t_env *env)
{
	*child = initialize_child(lex);
	*exec = initialize_exec(lex);
	if (!(*child) || !(*exec))
	{
		free_struct(*child, *exec, env);
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
	int		tmp;

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
			if (!check_syntax(lex))
			{
				add_history(lex->line);
				initialize_struct(&child, &exec, lex, env);
				if (!parser(lex, child, env))
				{
					if (!executor(child, exec, env))
						close_piping(exec);
					waitpid(exec->last_pid, &tmp, 0);
					while (wait(&tmp) > 0)
						continue ;
					if (WIFEXITED(tmp))
						g_exit_code = WEXITSTATUS(tmp);
				}
				free_struct(child, exec, env);
				free_lex(lex);
			}
		}
	}
	free_env(env);
	return (0);
}

// waitpid(exec->last_pid, &errno, 0);
// 				while (wait(NULL) > 0)
// 					continue ;
// 				if (WIFEXITED(errno))
// 					printf("%d\n", WEXITSTATUS(errno)); /* WEXITSTATUS(child_info) = $? */
