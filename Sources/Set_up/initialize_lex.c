/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_lex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:20:11 by amechain          #+#    #+#             */
/*   Updated: 2022/11/08 17:10:53 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**create_lexer_string(t_lex *lex)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (lex->line && lex->line[i])
	{
		while ((lex->line[i] != ' ' && lex->line[i + 1] == '|')
			|| (lex->line[i] != ' ' && lex->line[i] != '<'
				&& lex->line[i + 1] == '<') || (lex->line[i] != ' '
				&& lex->line[i] != '>' && lex->line[i + 1] == '>')
			|| (lex->line[i] == '<' && lex->line[i + 1] != '<'
				&& lex->line[i + 1] != ' ') || (lex->line[i] == '>'
				&& lex->line[i + 1] != '>' && lex->line[i + 1] != ' '))
		{
			lex->line2[j++] = lex->line[i++];
			lex->line2[j++] = ' ';
		}
		lex->line2[j++] = lex->line[i++];
	}
	free(lex->line);
	lex->lexer = split_lexer(lex->line2, ' ');
	free_doublepointer(split_lexer(lex->line2, ' '));
	free(lex->line2);
//	print_lexer(lex);
	return (lex->lexer);
}

int	lexer_count_spaces(t_lex *lex)
{
	int	i;

	i = 0;
	lex->counter = 0;
	while (lex->line && lex->line[i])
	{
		if (lex->line[i] != ' ' && lex->line[i + 1] == '|')
			lex->counter++;
		if (lex->line[i] != ' ' && lex->line[i] != '<'
			&& lex->line[i + 1] == '<')
			lex->counter++;
		if (lex->line[i] != ' ' && lex->line[i] != '>'
			&& lex->line[i + 1] == '>')
			lex->counter++;
		if (lex->line[i] == '<' && lex->line[i + 1]
			!= '<' && lex->line[i + 1] != ' ')
			lex->counter++;
		if (lex->line[i] == '>' && lex->line[i + 1]
			!= '>' && lex->line[i + 1] != ' ')
			lex->counter++;
		i++;
	}
	return (lex->counter);
}

t_lex	*initialize_lex(void)
{
	t_lex	*lex;

	lex = ft_calloc(1, sizeof(t_lex));
	if (lex == NULL)
		errorexit("check initializiation of lex");
	lex->line = readline("input: ");
	if (lex->line == NULL)
        errorexit("check initializiation of lex->line");
	lex->counter = lexer_count_spaces(lex);
	lex->iter = 0;
	lex->no_processes = 0;
	lex->line2 = ft_calloc(ft_strlen(lex->line) + lex->counter,
			(ft_strlen(lex->line) + lex->counter) * sizeof(char));
	if (lex->line2 == NULL)
		errorexit("malloc error line2");
	lex->lexer = create_lexer_string(lex);
	return (lex);
}
