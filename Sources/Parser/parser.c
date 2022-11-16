
#include "../../includes/minishell.h"

int	quote_management(t_lex *lex, t_child *child)
{
	int	i;
	int	z;

	i = 0;
	z = 0;
	while (lex->lexer[i] && lex->lexer)
	{
		if (!ft_strcmp(lex->lexer[i], "<<"))
		{
			i++;
			z = 0;
			while (lex->lexer[i][z])
			{
				if (lex->lexer[i][z] == 39 || lex->lexer[i][z] == '"')
				{
					child->heredoc_quotes = 1;
					break ;
				}
				z++;
			}
		}
		else if (!strcmp(lex->lexer[i], "<")
			|| !strcmp(lex->lexer[i], ">")
			|| !strcmp(lex->lexer[i], ">>")
			|| !strcmp(lex->lexer[i], "<<"))
			i++;
		else // HERE_DOC EOF $ IS NOT ALLOWED TO BE MARKED (should work now)
		{
			if (mark_quotes(lex->lexer[i], lex->lexer[i - 1]) != 0)
				return (1); //RETURN(1);
			lex->lexer[i] = delete_quotes(lex->lexer[i]);
			i++;
		}
	}
	return (0);
}

int	parser(t_lex *lex, t_child	**child) // DELETE QUOTES EXCEPT HERE_DOC // MARKING VARIABLES THAT SHOULD GET EXPAND AS -2
{
	int	k;

	k = 0;
	while (child[k])
	{
		if (quote_management(lex, child[k]))
			return (1);
		k++;
	}
	if (parse_commands(lex, child))
		return (1);
	if (parser_redirection(lex, child))
		return (1);
	return (0);
}
