/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:59:04 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/11 16:59:39 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_redirection_table(char **parser_redirect_input, int i, int j)
{
	int	k;

	k = 0;
	if (ft_strcmp(parser_redirect_input[i], "<")
		&& ft_strcmp(parser_redirect_input[i], "<<"))
		errorexit("Wrong redirection input\n");
	while (parser_redirect_input[j][k])
	{
		if (parser_redirect_input[j][k] == '|'
			|| parser_redirect_input[j][k] == '&'
			|| parser_redirect_input[j][k] == ';'
			|| parser_redirect_input[j][k] == '('
			|| parser_redirect_input[j][k] == ')'
			|| parser_redirect_input[j][k] == '<'
			|| parser_redirect_input[j][k] == '>'
			|| parser_redirect_input[j][k] == '$')
			errorexit("Wrong token filename");
		k++;
	}
}

void	parser(t_lex *lex, t_child	**child)
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
				while(lex->lexer[i++][z])
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
					return ; //RETURN(1);
				printf("STR after marking: %s\n", lex->lexer[i]);
				lex->lexer[i] = delete_quotes(lex->lexer[i]);
				i++;
			}
		}
		printf("QUOTES HEREDOC: %d\n", child[k]->heredoc_quotes);
		k++;
	}
	parse_commands(lex, child);
	parser_redirection(lex, child);
	print_lexer(lex);
	print_parser(child);
	// return (0);
}
