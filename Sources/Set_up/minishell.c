
#include "../../includes/minishell.h"

//char *exit_string;

void	print_lexer(t_lex *lex)
{
	int	i;

	i = 0;
	lex->iter = 0;
	while (lex->lexer[lex->iter])
	{
		printf("%s\n", lex->lexer[lex->iter]);
		lex->iter++;
	}
	printf("%s\n", lex->lexer[lex->iter]);
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
		//executed children (fork, pipe, call execve)
		while (waitpid(-1, &child_info, 0) != -1)
			continue ;
		if (WIFEXITED(child_info))
		{
			printf("%d\n", WEXITSTATUS(child_info));
		}
		if (lex->line && *(lex->line))
			add_history(lex->line);
		parser(lex, child);
		executor(lex, child, exec);
	}
	return (0);
}
