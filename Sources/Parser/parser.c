/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:59:04 by jmatheis          #+#    #+#             */
/*   Updated: 2022/10/26 17:34:44 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void count_pipes(t_lex *lex, t_child **child)
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
	// printf("%d\n", lex->noofpipes);
	child = malloc((c + 2) * sizeof(char *));
	if (child == NULL)
		errorexit("Child is NULL");
	
}

void parser(t_lex *lex, t_child **child)
{
	count_pipes(lex, child);
	parse_commands(lex, child);
}
