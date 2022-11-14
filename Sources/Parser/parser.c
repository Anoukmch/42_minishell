
#include "../../includes/minishell.h"

/* Is it necessary to connect this function ? */
// void	check_redirection_table(char **parser_redirect_input, int i, int j)
// {
// 	int	k;

// 	k = 0;
// 	if (ft_strcmp(parser_redirect_input[i], "<")
// 		&& ft_strcmp(parser_redirect_input[i], "<<"))
// 		errorexit("Wrong redirection input\n");
// 	while (parser_redirect_input[j][k])
// 	{
// 		if (parser_redirect_input[j][k] == '|'
// 			|| parser_redirect_input[j][k] == '&'
// 			|| parser_redirect_input[j][k] == ';'
// 			|| parser_redirect_input[j][k] == '('
// 			|| parser_redirect_input[j][k] == ')'
// 			|| parser_redirect_input[j][k] == '<'
// 			|| parser_redirect_input[j][k] == '>'
// 			|| parser_redirect_input[j][k] == '$')
// 			errorexit("wrong token filename");
// 		k++;
// 	}
// }

int	parser(t_lex *lex, t_child	**child)
{
	int	i;
	int	k;
	int	z;

	i = 0;
	k = 0;
	z = 0;
	// DELETE QUOTES EXCEPT HERE_DOC
	// MARKING VARIABLES THAT SHOULD GET EXPAND AS -2
	while (child[k])
	{
		while (lex->lexer[i] && lex->lexer) 
		{
			if (!ft_strcmp(lex->lexer[i], "<<"))
			{
				i++;
				z = 0;
				while(lex->lexer[i][z])
				{
					if (lex->lexer[i][z] == 39 || lex->lexer[i][z] == '"')
					{
						child[k]->heredoc_quotes = 1;
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
			else
			{
				// HERE_DOC EOF $ IS NOT ALLOWED TO BE MARKED (should work now)
				if (mark_quotes(lex->lexer[i], lex->lexer[i - 1]) != 0)
					return (1); //RETURN(1);
				lex->lexer[i] = delete_quotes(lex->lexer[i]);
				i++;
			}
		}
		k++;
	}
	if (parse_commands(lex, child))
		return (1);
	if (parser_redirection(lex, child))
		return (1);
	return (0);
}
