#include "../../includes/minishell.h"

int	fill_redirection_table(t_lex *lex, t_child *child)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	lex = (void *)lex;
	while (lex->lexer[lex->counter] && ft_strcmp(lex->lexer[lex->counter], "|"))
	{
		if (!ft_strcmp(lex->lexer[lex->counter], "<")
			|| !ft_strcmp(lex->lexer[lex->counter], "<<"))
		{
			child->parser_redirect_input[i++]
				= ft_strdup(lex->lexer[lex->counter++]);
			child->parser_redirect_input[i++]
				= ft_strdup(lex->lexer[lex->counter]);
			if (!child->parser_redirect_input[i - 1]
				|| !child->parser_redirect_input[i - 2])
				return (1);
		}
		else if (!ft_strcmp(lex->lexer[lex->counter], ">")
			|| !ft_strcmp(lex->lexer[lex->counter], ">>"))
		{
			child->parser_redirect_output[j++]
				= ft_strdup(lex->lexer[lex->counter++]);
			child->parser_redirect_output[j++]
				= ft_strdup(lex->lexer[lex->counter]);
			if (!child->parser_redirect_output[j - 1]
				|| !child->parser_redirect_output[j - 2])
				return (1);
		}
		lex->counter++;
	}
	child->parser_redirect_input[i] = NULL;
	child->parser_redirect_output[j] = NULL;
	return (0);
}

int	parser_redirection(t_lex *lex, t_child **child)
{
	int	i;

	i = 0;
	lex->counter = 0;
	while (child[i])
	{
		if (fill_redirection_table(lex, child[i]))
			return (1);
		i++;
		lex->counter++;
	}
	return (0);
}
