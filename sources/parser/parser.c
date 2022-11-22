/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:25:40 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/22 15:25:41 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	free_struct(NULL, NULL, lex);
	return (0);
}
