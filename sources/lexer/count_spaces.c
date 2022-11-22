/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:24:21 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/22 15:24:22 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	spaces_before_quotes(t_lex *lex, int i)
{
	if (lex->line[i + 1])
	{
		if (lex->line[i] == '|' && lex->line[i + 1] != ' ')
			lex->counter++;
		else if (lex->line[i] == '<'
			&& lex->line[i + 1] != '<' && lex->line[i + 1] != ' ')
			lex->counter++;
		else if (lex->line[i] == '>'
			&& lex->line[i + 1] != '>' && lex->line[i + 1] != ' ')
			lex->counter++;
		else if (lex->line[i + 1] == '|' && lex->line[i] != ' ')
			lex->counter++;
		else if (lex->line[i + 1] == '<'
			&& lex->line[i] != '<' && lex->line[i] != ' ')
			lex->counter++;
		else if (lex->line[i + 1] == '>'
			&& lex->line[i] != '>' && lex->line[i] != ' ')
			lex->counter++;
	}
}

int	lexer_count_spaces(t_lex *lex)
{
	int		i;
	char	quote;

	quote = 's';
	i = 0;
	lex->counter = 0;
	while (lex->line[i] != '\0')
	{
		skipquotes(&quote, lex->line[i]);
		if (quote == '\0')
			spaces_before_quotes(lex, i);
		i++;
	}
	return (lex->counter);
}
