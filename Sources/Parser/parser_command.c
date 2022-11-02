/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:18:25 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/02 15:57:19 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
grep "hello world" >outfile | 'my name is' > infile
*/
static void	commands(t_lex *lex, t_child **child, int k)
{
	int	j;

	j = 0;
	while (lex->lexer[lex->iter]
		&& (ft_strncmp(lex->lexer[lex->iter], "|", 2) != 0))
	{
		if ((ft_strncmp(lex->lexer[lex->iter], "<", 2) == 0
				|| ft_strncmp(lex->lexer[lex->iter], "<<", 3) == 0
				|| ft_strncmp(lex->lexer[lex->iter], ">", 2) == 0
				|| ft_strncmp(lex->lexer[lex->iter], ">>", 3) == 0))
			lex->iter += 2;
		else
		{
			child[k]->parser_cmd[j] = ft_substr(lex->lexer[lex->iter],
				0, ft_strlen(lex->lexer[lex->iter]));
			if (!child[k]->parser_cmd[j])
				errorexit("Allocation failed");
			printf("CMD[%d][%d]: %s\n", k, j, child[k]->parser_cmd[j] = lex->lexer[lex->iter]);
			j++;
			lex->iter++;
		}
	}
	child[k]->parser_cmd[j] = NULL;
}

void	parse_commands(t_lex *lex, t_child **child)
{
	int	k;

	k = 0;
	lex->iter = 0;
	while (k < lex->no_processes)
	{
		commands(lex, child, k);
		lex->iter++;
		k++;
	}
}
