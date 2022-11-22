/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:25:32 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/22 15:25:33 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	split_first_command(t_lex *lex, t_child *child, int *j)
{
	int	z;

	z = check_first_command(lex, child, j);
	if (z == 1)
		return (1);
	if (z == 2)
	{
			child->parser_cmd[*j] = ft_strdup(lex->lexer[lex->iter]);
		if (!child->parser_cmd[*j])
			return (1);
		if (mark_quotes_cmds_and_outdir(child->parser_cmd[*j]))
			return (1);
		child->parser_cmd[*j] = delete_quotes_cmds_and_outdir
			(child->parser_cmd[*j]);
	}
	return (0);
}

int	add_lexcommand_to_child(t_lex *lex, t_child *child, int *j)
{
	child->parser_cmd[*j] = ft_strdup(lex->lexer[lex->iter]);
	if (!child->parser_cmd[*j])
		return (1);
	if (mark_quotes_cmds_and_outdir(child->parser_cmd[*j]))
		return (1);
	child->parser_cmd[*j] = delete_quotes_cmds_and_outdir
		(child->parser_cmd[*j]);
	return (0);
}

int	commands(t_lex *lex, t_child *child, int j)
{
	while (lex->lexer[lex->iter]
		&& ft_strcmp(lex->lexer[lex->iter], "|"))
	{
		if (!ft_strcmp(lex->lexer[lex->iter], "<")
			|| !ft_strcmp(lex->lexer[lex->iter], "<<")
			|| !ft_strcmp(lex->lexer[lex->iter], ">")
			|| !ft_strcmp(lex->lexer[lex->iter], ">>"))
			lex->iter += 2;
		else
		{
			if (j == 0)
			{
				if (split_first_command(lex, child, &j))
					return (1);
			}
			else if (j != 0 && add_lexcommand_to_child(lex, child, &j))
				return (1);
			j++;
			lex->iter++;
		}
	}
	child->parser_cmd[j] = NULL;
	return (0);
}

int	parse_commands(t_lex *lex, t_child **child)
{
	int	k;
	int	j;

	k = 0;
	j = 0;
	lex->iter = 0;
	while (k < lex->no_processes)
	{
		if (commands(lex, child[k], j))
			return (1);
		lex->iter++;
		k++;
	}
	return (0);
}
