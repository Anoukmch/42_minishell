/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_child.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:32:34 by amechain          #+#    #+#             */
/*   Updated: 2022/11/11 19:56:07 by amechain         ###   ########.fr       */
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

static void	init_cmds(t_lex *lex, t_child **child, int k)
{
	child[k]->no_cmd_opt = 0;
	child[k]->input_counter = 0;
	child[k]->output_counter = 0;
	while (lex->lexer[lex->iter]
		&& ft_strncmp(lex->lexer[lex->iter], "|", 2) != 0)
	{
		if (ft_strncmp(lex->lexer[lex->iter], "<", 2) == 0
			|| ft_strncmp(lex->lexer[lex->iter], "<<", 3) == 0)
		{
			child[k]->input_counter += 2;
			lex->iter += 2;
		}
		else if (ft_strncmp(lex->lexer[lex->iter], ">", 2) == 0
			|| ft_strncmp(lex->lexer[lex->iter], ">>", 3) == 0)
		{
			child[k]->output_counter += 2;
			lex->iter += 2;
		}
		else
		{
			child[k]->no_cmd_opt++;
			lex->iter++;
		}
	}
	lex->iter++;
}

t_child	**initialize_child(t_lex *lex)
{
	t_child	**child;
	int		k;

	k = 0;
	count_processes(lex);
	child = ft_calloc(lex->no_processes + 1, sizeof(t_child *));
	if (child == NULL)
		errorexit("check initializiation of arrays of child");
	lex->iter = 0;
	while (k < lex->no_processes)
	{
		child[k] = ft_calloc(1, sizeof(t_child));
		if (child[k] == NULL)
			errorexit("check initializiation of child calloc");
		init_cmds(lex, child, k);
		child[k]->parser_cmd
			= ft_calloc(child[k]->no_cmd_opt + 1, sizeof(char *));
		child[k]->parser_redirect_input
			= ft_calloc(child[k]->input_counter + 1, sizeof(char *));
		child[k]->parser_redirect_output
			= ft_calloc(child[k]->output_counter + 1, sizeof(char *));
		if (child[k]->parser_redirect_output == NULL
			|| child[k]->parser_redirect_input == NULL
			|| child[k]->parser_cmd == NULL)
			errorexit("check initializiation of child arrays");
		child[k]->command = NULL;
		child[k]->fd_in = -1;
		child[k]->fd_out = -1;
		child[k]->id = k;
		child[k]->isbuiltin = false;
		k++;
	}
	child[lex->no_processes] = NULL;
	return (child);
}
