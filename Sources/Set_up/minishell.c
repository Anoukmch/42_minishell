#include "../../includes/minishell.h"

int	g_exit_code = 0;

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	free_struct(t_child	**child, t_exec	*exec)
{
	int	i;

	i = 0;
	if (child)
	{
		while (child[i])
		{
			free_array(child[i]->parser_cmd);
			free_array(child[i]->parser_redirect_input);
			free_array(child[i]->parser_redirect_output);
			free(child[i]->command);
			free(child[i]);
			i++;
		}
		free(child);
	}
	if (exec)
		free(exec);
}

void	close_piping(t_exec	*exec)
{
	if (exec->nbr_process > 1)
	{
		close(exec->end[0]);
		close(exec->end[1]);
	}
}

void	free_lex(t_lex	*lex)
{
	free(lex->line);
	free(lex->line2);
	free_array(lex->lexer);
	free(lex);
}

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
		return (1); /* Change that */
	signal(SIGQUIT, SIG_IGN);
	env = initialize_env(envp);
	while (1)
	{
		handle_signals();
		lex = initialize_lex();
		// print_lexer(lex);
		if (lex)
		{
			if (!check_syntax(lex)) /* where is the parser and initialize ? */
			{
				add_history(lex->line);
				initialize_struct(&child, &exec, lex);
				if (!parser(lex, child))
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
	free_array(env->envp_bis);
	free_array(env->envp_path);
	free(env->envp_line);
	free(env);
	return (0);
}

// waitpid(exec->last_pid, &errno, 0);
// 				while (wait(NULL) > 0)
// 					continue ;
// 				if (WIFEXITED(errno))
// 					printf("%d\n", WEXITSTATUS(errno)); /* WEXITSTATUS(child_info) = $? */
