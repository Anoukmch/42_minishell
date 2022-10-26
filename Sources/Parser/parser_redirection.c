/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:01:43 by amechain          #+#    #+#             */
/*   Updated: 2022/10/26 14:14:11 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parse_redirection(t_lex *lex, t_child **child)
{
	int	i;
	int j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (child[k]) /* t_child **child needs to be NULL terminated */
	{
		while (lex->lexer[i] != "|" && lex->lexer[i])  /* If we never enter the condition, then child->parser_redirect[0] remains NULL */
		{
			j = 0;
			if (lex->lexer[i] == "<" || lex->lexer[i] == "<<")
			{
				child[k]->parser_redirect_input[j++] = lex->lexer[i++];
				child[k]->parser_redirect_input[j++] = lex->lexer[i];
			}
			j = 0;
			else if (lex->lexer[i] == ">" || lex->lexer[i] == ">>")
			{
				child[k]->parser_redirect_output[j++] = lex->lexer[i++];
				child[k]->parser_redirect_output[j++] = lex->lexer[i];
			}
			i++;
		}
		i++;
		k++;
	}
}
