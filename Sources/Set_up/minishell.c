

#include "../../includes/minishell.h"

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
	{
		free_array(exec->envp_path);
		free(exec);
	}
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
	if (lex)
	{
		free(lex->line);
		free(lex->line2);
		free_array(lex->lexer);
		free(lex);
	}
}

void	initialize_struct(t_child	***child, t_exec	**exec, t_lex *lex, char **envp)
{
	*child = initialize_child(lex);
	*exec = initialize_exec(lex, envp);
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

	child = NULL;
	exec = NULL;
	if (ac == 1 && ag[0])
	{
		while (1)
		{
			handle_signals();
			lex = initialize_lex();
			if (lex)
			{
				add_history(lex->line);
				initialize_struct(&child, &exec, lex, envp);
				if (!parser(lex, child))
				{
					if (!executor(lex, child, exec))
						close_piping(exec);
				}
				// waitpid(exec->last_pid, &errno, 0);
				// while (wait(NULL) > 0)
				// 	continue ;
				// if (WIFEXITED(errno))
				// 	printf("%d\n", WEXITSTATUS(errno)); /* WEXITSTATUS(child_info) = $? */
				// free_struct(child, exec);
				// free_lex(lex);
			}
		}
	}
	return (0);
}

// while (waitpid(0, &exit_code, 0) != -1)
//         			continue ;
