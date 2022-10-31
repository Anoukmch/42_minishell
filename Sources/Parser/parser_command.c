/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:18:25 by jmatheis          #+#    #+#             */
/*   Updated: 2022/10/31 14:33:45 by jmatheis         ###   ########.fr       */
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
		while (lex->lexer[lex->iter]
			&& (ft_strncmp(lex->lexer[lex->iter], "<", 2) == 0
				|| ft_strncmp(lex->lexer[lex->iter], "<<", 3) == 0
				|| ft_strncmp(lex->lexer[lex->iter], ">", 2) == 0
				|| ft_strncmp(lex->lexer[lex->iter], ">>", 3) == 0))
		{
			if (!lex->lexer[lex->iter + 2])
			{
				lex->iter++;
				return ;
			}
			else
				lex->iter += 2;
		}
		free(lex->lexer[lex->iter]);
		child[k]->parser_cmd[j] = ft_substr(lex->lexer[lex->iter],
				0, ft_strlen(lex->lexer[lex->iter]));
		// PRINT PARSER_COMMANDS
		printf("CMD[%d][%d]: %s\n", k, j, child[k]->parser_cmd[j] = lex->lexer[lex->iter]);
		j++;
		lex->iter++;
	}
}

void	parse_commands(t_lex *lex, t_child **child)
{
	int	k;

	k = 0;
	lex->iter = 0;
	while (k <= lex->no_processes)
	{
		commands(lex, child, k);
		lex->iter++;
		k++;
	}
	child[k] = NULL;
	exit(0);
}
