#include "../../includes/minishell.h"

void free_lexer(t_lex *lex)
{
	if (lex)
	{
		free(lex->line);
		free(lex->line2);
		free_array(lex->lexer);
		free(lex);
	}
}

int	parser(t_lex *lex, t_child	**child, t_env	*env)
{
	int	i;

	i = 0;
	if (!lex->line[0])
		return (1);
	while (lex->lexer[i])
	{
		if (i > 0 && mark_variables(lex->lexer[i], lex->lexer[i - 1]))
			return (1);
		else if (mark_variables(lex->lexer[i], NULL))
			return (1);
		if (check_dollarsign(lex->lexer[i]))
			return (1);
		if (quotes_after_dollarsign(lex, i))
			return (1);
		i++;
	}
	if (var_handler(lex, env))
		return (1);
	if (parser_redirection(lex, child))
		return (1);
	if (parse_commands(lex, child))
		return (1);
	// FREE LEXER HERE !!!
	return (0);
}
