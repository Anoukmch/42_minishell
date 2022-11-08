/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:19:33 by amechain          #+#    #+#             */
/*   Updated: 2022/11/08 13:04:44 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	close_pipe_bis(t_child	**child, t_exec	*exec)
{
	int	i;

	i = 0;
	while (child[i])
	{
		if (exec->nbr_process > 1)
		{
			close(exec->end[0]);
			close(exec->end[1]);
			if (child[i]->id != 0 && child[i]->id != (exec->nbr_process - 1))
				close(exec->buffer[0]);
		}
		if (child[i]->parser_redirect_input[0] != NULL)
			close(child[i]->fd_in);
		if (child[i]->parser_redirect_output[0] != NULL)
			close(child[i]->fd_out);
		i++;
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
		child = initialize_child(lex);
		exec = initialize_exec(lex, envp);
		if (lex->line && *(lex->line))
			add_history(lex->line);
		parser(lex, child);
		executor(lex, child, exec);
		close_pipe_bis(child, exec);
 		while (waitpid(-1, &child_info, 0) != -1)
         continue ;
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
