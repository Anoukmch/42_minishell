/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:25:07 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/22 15:25:08 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	var_handler(t_lex *lex, t_env *env)
{
	int		i;

	i = 0;
	while (lex->lexer[i])
	{
		if (ft_strchr(lex->lexer[i], -2) != NULL)
		{
			lex->lexer[i] = handle_var(lex->lexer[i], env);
			if (!lex->lexer[i])
				return (1);
		}
		i++;
	}
	lex->lexer = rebuild_lex(lex);
	return (0);
}
