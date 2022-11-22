/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:21:23 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/22 15:21:26 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	read_input(t_lex *lex, t_env *env)
{
	if (isatty(STDIN_FILENO))
	{
		lex->line = readline("input: ");
		signal(SIGINT, SIG_IGN);
	}
	if (lex->line == NULL)
	{
		if (isatty(STDERR_FILENO))
		{
			free_env(env);
			rl_clear_history();
			if (lex)
				free_struct(NULL, NULL, lex);
			ft_putstr_fd("exit\n", STDERR_FILENO);
		}
		exit (g_exit_code);
	}
	else if (!lex->line[0])
		return (1);
	return (0);
}

void	init_lex_bis(t_lex *lex, t_env *env)
{
	lex->counter = lexer_count_spaces(lex);
	lex->iter = 0;
	lex->no_processes = 0;
	lex->line2 = ft_calloc((ft_strlen(lex->line) + 1)
			+ lex->counter, sizeof(char));
	if (!lex->line2)
	{
		free_struct_lex(lex);
		free_env(env);
		exit (g_exit_code);
	}
}

t_lex	*initialize_lex(t_env *env)
{
	t_lex	*lex;

	lex = ft_calloc(1, sizeof(t_lex));
	if (!lex)
		return (NULL);
	if (read_input(lex, env))
		return (free_struct_lex(lex));
	lex->line = convert_tabs_to_spaces(lex->line);
	if (!lex->line)
		return (free_struct_lex(lex));
	init_lex_bis(lex, env);
	create_line2(lex);
	lex->lexer = ft_split(lex->line2, -1);
	if (!lex->lexer || !lex->lexer[0])
		return (free_struct_lex(lex));
	lex->lexer_c = NULL;
	if (check_syntax(lex))
		return (free_struct_lex(lex));
	return (lex);
}
