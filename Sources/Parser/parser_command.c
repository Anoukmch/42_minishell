/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:18:25 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/10 19:51:19 by jmatheis         ###   ########.fr       */
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
			lex->lexer[lex->iter] = mark_quotes(lex->lexer[lex->iter]);
			child[k]->parser_cmd[j] = delete_quotes(lex->lexer[lex->iter]);
			if (!child[k]->parser_cmd[j])
				errorexit("Allocation failed");
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
