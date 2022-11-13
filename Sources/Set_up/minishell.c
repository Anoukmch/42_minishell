

#include "../../includes/minishell.h"

int	exit_code = 0;

//char *exit_string;

// void	print_lexer(t_lex *lex)
// {
// 	int	i;

// 	i = 0;
// 	lex->iter = 0;
// 	while (lex->lexer[lex->iter])
// 	{
// 		printf("%s\n", lex->lexer[lex->iter]);
// 		lex->iter++;
// 	}
// 	printf("%s\n", lex->lexer[lex->iter]);
// }

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

void	freeing(t_child	**child, t_exec	*exec)
{
	int	i;

	i = 0;
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
	free_array(exec->envp_path);
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

int	main(int ac, char **ag, char **envp)
{
	t_lex	*lex;
	t_child	**child;
	t_exec	*exec;
	int		child_info;

	if (ac != 1 || !ag[0])
		errorexit("Wrong number of arguments");
	while (1)
	{
		handle_signals();
		lex = initialize_lex();
		if (lex->line && lex->line[0])
		{
			add_history(lex->line);
			child = initialize_child(lex);
			exec = initialize_exec(lex, envp);
			parser(lex, child);
			executor(lex, child, exec);
			close_piping(exec);
			// exec->last_pid instead of 0
 			while (waitpid(0, &child_info, 0) != -1)
        		continue ;
				// waitpid(exec->last_pid, &child_info, 0)
				// while (wait(NULL) > 0)
					// continue ;
			freeing(child, exec);
		}
		free(lex->line);
		free_array(lex->lexer);
		free(lex);
        // waitpid(-1, NULL, 0);
        // while (wait(NULL) != -1)
        //  continue ;
		// if (WIFEXITED(child_info))
		// {
		// 	printf("%d\n", WEXITSTATUS(child_info));
		/* if i remember correctly, WEXITSTATUS(child_info) = $? */
		// }
	}
	return(0);
}
