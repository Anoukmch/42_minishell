/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:01:43 by amechain          #+#    #+#             */
/*   Updated: 2022/10/26 15:05:42 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_input_table(t_lex *lex, t_child *child)
{
	int	i;

	i = 0;
	while (lex->lexer[lex->counter] != "|" && lex->lexer[lex->counter])  /* If we never enter the condition, then child->parser_redirect[0] remains NULL */
	{
		if (lex->lexer[lex->counter] == "<" || lex->lexer[lex->counter] == "<<")
		{
			child->parser_redirect_input[i++] = lex->lexer[lex->counter++];
			child->parser_redirect_input[i++] = lex->lexer[lex->counter];
		}
		lex->counter++;
	}
}

void	create_output_table(t_lex *lex, t_child *child)
{
	int	i;

	i = 0;
	while (lex->lexer[lex->counter] != "|" && lex->lexer[lex->counter])  /* If we never enter the condition, then child->parser_redirect[0] remains NULL */
	{
		if (lex->lexer[lex->counter] == ">" || lex->lexer[lex->counter] == ">>")
		{
			child->parser_redirect_output[i++] = lex->lexer[lex->counter++];
			child->parser_redirect_output[i++] = lex->lexer[lex->counter];
		}
		lex->counter++;
	}
}

void	parse_redirection(t_lex *lex, t_child **child)
{
	int	i;

	i = 0;
	while (child[i]) /* t_child **child needs to be NULL terminated */
	{
		create_input_table(lex, child[k]);
		create_output_table(lex, child[k]);
	}
	i++;
}


lex->lexer[0] = <<       			child->parser_redirect_input[0] = <<
lex->lexer[1] = eof					child->parser_redirect_input[1] = eof
lex->lexer[2] = <					child->parser_redirect_input[2] = <
lex->lexer[3] = "Makefile"			child->parser_redirect_input[3] = "Makefile"
lex->lexer[4] = <<					child->parser_redirect_input[4] = <<
lex->lexer[5] = eof					child->parser_redirect_input[5] = eof
lex->lexer[6] = ls
lex->lexer[7] = -al
lex->lexer[8] = >
lex->lexer[9] = outfile
lex->lexer[10] = |
lex->lexer[11] = grep
lex->lexer[12] = libs
lex->lexer[13] = >
lex->lexer[14] = outfile

char **child->parser_redirect;
child->parser_redirect[i];
