/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lexline2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:24:25 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/22 15:24:26 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	check_outside_quotes(t_lex *lex, int *j, int *i)
{
	if (lex->line[*i + 1])
	{
		if ((lex->line[*i] == '|' && lex->line[*i + 1] != ' ')
			|| (lex->line[*i] == '<' && lex->line[*i + 1] != '<'
				&& lex->line[*i + 1] != ' ') || (lex->line[*i] == '>'
				&& lex->line[*i + 1] != '>' && lex->line[*i + 1] != ' '))
		{
			lex->line2[(*j)++] = lex->line[(*i)++];
			lex->line2[(*j)++] = -1;
		}
		else if ((lex->line[*i + 1] == '|' && lex->line[*i] != ' ')
			|| (lex->line[*i + 1] == '<' && lex->line[*i] != '<'
				&& lex->line[*i] != ' ') || (lex->line[*i + 1] == '>'
				&& lex->line[*i] != '>' && lex->line[*i] != ' '))
		{
			lex->line2[(*j)++] = lex->line[(*i)++];
			lex->line2[(*j)++] = -1;
		}
	}
}

void	create_line2(t_lex *lex)
{
	int		i;
	int		j;
	char	quote;

	quote = 's';
	i = 0;
	j = 0;
	while (lex->line[i])
	{
		skipquotes(&quote, lex->line[i]);
		if (quote == '\0')
			check_outside_quotes(lex, &j, &i);
		if (quote == '\0' && lex->line[i] == ' ')
			lex->line2[j] = -1;
		else
			lex->line2[j] = lex->line[i];
		j++;
		i++;
	}
}
