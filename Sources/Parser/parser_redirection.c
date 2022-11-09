/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:01:43 by amechain          #+#    #+#             */
/*   Updated: 2022/11/09 12:39:07 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fill_redirection_table(t_lex *lex, t_child *child)
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
				= ft_substr(lex->lexer[lex->counter++], 0, 2);
			child->parser_redirect_input[i++]
				= ft_substr(lex->lexer[lex->counter],
					0, ft_strlen(lex->lexer[lex->counter]));
			if (!child->parser_redirect_input[i - 1]
				|| !child->parser_redirect_input[i - 2])
				errorexit("Allocation failed");
		}
		else if (!ft_strcmp(lex->lexer[lex->counter], ">")
			|| !ft_strcmp(lex->lexer[lex->counter], ">>"))
		{
			child->parser_redirect_output[j++]
				= ft_substr(lex->lexer[lex->counter++], 0, 2);
			child->parser_redirect_output[j++]
				= ft_substr(lex->lexer[lex->counter],
					0, ft_strlen(lex->lexer[lex->counter]));
			if (!child->parser_redirect_output[j - 1]
				|| !child->parser_redirect_output[j - 2])
				errorexit("Allocation failed");
		}
		lex->counter++;
	}
	child->parser_redirect_input[i] = NULL;
	child->parser_redirect_output[j] = NULL;
}

void	parser_redirection(t_lex *lex, t_child **child)
{
	int	i;

	i = 0;
	lex->counter = 0;
	while (child[i])
	{
		fill_redirection_table(lex, child[i]);
		i++;
		lex->counter++;
	}
}
