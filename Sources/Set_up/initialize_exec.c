#include "../../includes/minishell.h"

t_exec	*initialize_exec(t_lex *lex)
{
	t_exec	*exec;
	int		i;

	i = 0;
	exec = ft_calloc(1, sizeof(t_exec));
	if (exec == NULL)
		perror_return("check initializiation of exec");
	exec->nbr_process = lex->no_processes;
	exec->end[0] = 0;
	exec->end[1] = 0;
	exec->buffer[0] = 0;
	exec->isheredoc = 0;
	return (exec);
}
