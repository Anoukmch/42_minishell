/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:59:04 by jmatheis          #+#    #+#             */
/*   Updated: 2022/10/29 19:05:33 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void count_pipes(t_lex *lex)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while(lex->lexer && lex->lexer[i])
	{
		if(ft_strncmp(lex->lexer[i], "|", 2) == 0)
		{
			c++;
		}
		i++;
	}
	lex->noofpipes = c;	
}

void parser(t_lex *lex, t_child **child)
{
	parse_commands(lex, child);
}

//  grep "hello world" >outfile