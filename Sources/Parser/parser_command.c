#include "../../includes/minishell.h"

int	commands(t_lex *lex, t_child *child)
{
	int	j;

	j = 0;
	while (lex->lexer[lex->iter]
		&& ft_strcmp(lex->lexer[lex->iter], "|"))
	{
		if (!ft_strcmp(lex->lexer[lex->iter], "<")
			|| !ft_strcmp(lex->lexer[lex->iter], "<<")
			|| !ft_strcmp(lex->lexer[lex->iter], ">")
			|| !ft_strcmp(lex->lexer[lex->iter], ">>"))
			lex->iter += 2;
		else
		{
			if (mark_quotes_cmds_and_outdir(lex->lexer[lex->iter]))
				return (1);
			lex->lexer[lex->iter] = delete_quotes_cmds_and_outdir
				(lex->lexer[lex->iter]);
			child->parser_cmd[j] = ft_strdup(lex->lexer[lex->iter]);
			if (!child->parser_cmd[j])
				return (1);
			j++;
			lex->iter++;
		}
	}
	child->parser_cmd[j] = NULL;
	return (0);
}

int	parse_commands(t_lex *lex, t_child **child)
{
	int	k;

	k = 0;
	lex->iter = 0;
	while (k < lex->no_processes)
	{
		if (commands(lex, child[k]))
			return (1);
		lex->iter++;
		k++;
	}
	return (0);
}
