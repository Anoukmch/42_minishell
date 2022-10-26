/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:01:43 by amechain          #+#    #+#             */
/*   Updated: 2022/10/26 16:32:59 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*fill_redirection_table(t_lex *lex, t_child *child)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (ft_strcmp(lex->lexer[lex->counter], "|") && lex->lexer[lex->counter])  /* If we never enter the condition, then child->parser_redirect[0] remains NULL */
	{
		if (!ft_strcmp(lex->lexer[lex->counter], "<") || !ft_strcmp(lex->lexer[lex->counter], "<<"))
		{
			child->parser_redirect_input[i++] = lex->lexer[lex->counter++];
			child->parser_redirect_input[i++] = lex->lexer[lex->counter];
		}
		else if (!ft_strcmp(lex->lexer[lex->counter], ">") || !ft_strcmp(lex->lexer[lex->counter], ">>"))
		{
			child->parser_redirect_output[j++] = lex->lexer[lex->counter++];
			child->parser_redirect_output[j++] = lex->lexer[lex->counter];
		}
		lex->counter++;
	}
	child->parser_redirect_input[i] = NULL;
	child->parser_redirect_output[j] = NULL;
	if (i > 2)
		return ("Multiple input");
	else if (j > 2)
		return ("Multiple output");
	else
		return (NULL);
}

void	is_multiple_input(t_lex *lex, t_child *child)
{
	int	i;

	i = 0;
}

void	parser_redirection(t_lex *lex, t_child **child)
{
	int	i;

	i = 0;
	while (child[i]) /* t_child **child needs to be NULL terminated */
	{
		if (fill_redirection_table(lex, child[i]) == 1)
			create_redirection_table();
		lex->counter++;
		i++;
	}
	create_redirection_table(lex, child[i]);
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
