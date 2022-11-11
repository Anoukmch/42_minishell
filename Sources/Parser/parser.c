/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:59:04 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/11 18:20:56 by amechain         ###   ########.fr       */
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

	i = 0;
	k = 0;
	// DELETE QUOTES EXCEPT HERE_DOC
	// MARKING VARIABLES THAT SHOULD GET EXPAND AS -2
	while (child[k])
	{
		while (lex->lexer[i] && lex->lexer)
		{
			if (!ft_strcmp(lex->lexer[i], "<<"))
				i += 2;
			// else if (!ft_strcmp(lex->lexer[i], "<")
			// 	|| !ft_strcmp(lex->lexer[i], ">")
			// 	|| !ft_strcmp(lex->lexer[i], ">>"))
			// 	i++;
			else
			{
				if (mark_quotes(lex->lexer[i]) != 0)
					return ; //RETURN(1);
				lex->lexer[i] = delete_quotes(lex->lexer[i]);
				i++;
			}
		}
		k++;
	}
	parse_commands(lex, child);
	parser_redirection(lex, child);
	// printf("TEST\n");
	// print_lexer(lex);
	print_parser(child);
	// return (0);
}
