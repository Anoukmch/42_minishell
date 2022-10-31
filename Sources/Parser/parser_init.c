/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 11:16:46 by jmatheis          #+#    #+#             */
/*   Updated: 2022/10/31 17:09:00 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	count_processes(t_lex *lex)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (lex->lexer && lex->lexer[i])
	{
		if (ft_strncmp(lex->lexer[i], "|", 2) == 0)
			c++;
		i++;
	}
	lex->no_processes = c + 1;
}

// static void	init_cmds(t_lex *lex, t_child **child, int k)
// {
// 	// while (ft_strcmp(lex->lexer[lex->counter], "|")
// 	// 	&& lex->lexer[lex->iter])
// 	// {
// 	// 	while (lex->lexer[lex->iter + 2]
// 	// 		&& (ft_strncmp(lex->lexer[lex->iter], "<", 2) == 0
// 	// 			|| ft_strncmp(lex->lexer[lex->iter], "<<", 3) == 0
// 	// 			|| ft_strncmp(lex->lexer[lex->iter], ">", 2) == 0
// 	// 			|| ft_strncmp(lex->lexer[lex->iter], ">>", 3) == 0))
// 	// 	{
// 	// 		if (!lex->lexer[lex->iter + 2])
// 	// 		{
// 	// 			lex->iter++;
// 	// 			return ;
// 	// 		}
// 	// 		else
// 	// 			lex->iter += 2;
// 	// 	}
// 	// 	child[k]->no_cmd_opt++;
// 	// 	lex->iter++;
// 		if (ft_strncmp(lex->lexer[lex->iter], "<", 2) == 0
// 				|| ft_strncmp(lex->lexer[lex->iter], "<<", 3) == 0)
// 			child[k]->input_counter += 2;
// 		else if (ft_strncmp(lex->lexer[lex->iter], ">", 2) == 0
// 				|| ft_strncmp(lex->lexer[lex->iter], ">>", 3) == 0)
// 			child[k]->output_counter += 2;
// 		else
// 			child[k]->no_cmd_opt++;
// 		lex->iter++;
// 	}
// }

/* WITH IF CONDITION --> NO SEGFAULT, WORKS!
*/
static void	init_cmds(t_lex *lex, t_child **child, int k)
{
	while (lex->lexer[lex->iter]
		&& (ft_strncmp(lex->lexer[lex->iter], "|", 2) != 0))
	{
		while (lex->lexer[lex->iter]
			&& (ft_strncmp(lex->lexer[lex->iter], "<", 2) == 0
				|| ft_strncmp(lex->lexer[lex->iter], "<<", 3) == 0
				|| ft_strncmp(lex->lexer[lex->iter], ">", 2) == 0
				|| ft_strncmp(lex->lexer[lex->iter], ">>", 3) == 0))
		{
			if (ft_strncmp(lex->lexer[lex->iter], "<", 2) == 0
				|| ft_strncmp(lex->lexer[lex->iter], "<<", 3) == 0)
					child[k]->input_counter += 2;
			else if (ft_strncmp(lex->lexer[lex->iter], ">", 2) == 0
				|| ft_strncmp(lex->lexer[lex->iter], ">>", 3) == 0)
					child[k]->output_counter += 2;
			if (!lex->lexer[lex->iter + 2])
			{
				lex->iter++;
				return ;
			}
			else
				lex->iter += 2;
		}
		(child[k]->no_cmd_opt)++;
		lex->iter++;
	}
}

t_child	**init_child(t_lex *lex, t_child **child)
{
	int	k;

	k = 0;
	count_processes(lex);
	child = ft_calloc(lex->no_processes + 1, sizeof(t_child *));
	if (child == NULL)
		errorexit("check initializiation of structs");
	child[lex->no_processes + 1] = NULL;
	lex->iter = 0;
	while (k <= lex->no_processes)
	{
		child[k] = ft_calloc(1, sizeof(t_child));
		if (child[k] == NULL)
			errorexit("check initializiation of structs");
		child[k]->no_cmd_opt = 0;
		child[k]->input_counter = 0;
		child[k]->output_counter = 0;
		init_cmds(lex, child, k);
		lex->iter++;
		child[k]->parser_cmd
			= ft_calloc(child[k]->no_cmd_opt + 1, sizeof(char *));
		child[k]->parser_redirect_input
			= ft_calloc(child[k]->input_counter + 1, sizeof(char *));
		child[k]->parser_redirect_output
			= ft_calloc(child[k]->output_counter + 1, sizeof(char *));
		if (child[k]->parser_redirect_output == NULL || child[k]->parser_redirect_input == NULL
			|| child[k]->parser_cmd == NULL)
			errorexit("check initializiation of structs");
		k++;
	}
	return (child);
}
