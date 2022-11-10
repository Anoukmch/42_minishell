/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_lex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:20:11 by amechain          #+#    #+#             */
/*   Updated: 2022/11/10 17:37:32 by jmatheis         ###   ########.fr       */
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
		// TOO MANY SPACES? QUOTES!
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

static char	*convert_tabs_to_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\t' || str[i] == '\n')
		{
			while (str[i] == '\t' || str[i] == '\n')
				str[i++] = ' ';
		}
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"' && str[i] != '\0')
				i++;
		}
		if (str[i] == 39)
		{
			i++;
			while (str[i] != 39 && str[i] != '\0')
				i++;
		}
		i++;
	}
	return (str);
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
	else if (!lex->line[0])
		return (lex);
	// CONVERT TABS TO SPACES IF OUTSIDE OF STRING
	lex->line = convert_tabs_to_spaces(lex->line);
	lex->counter = lexer_count_spaces(lex);
	lex->iter = 0;
	lex->no_processes = 0;
	lex->line2 = ft_calloc(ft_strlen(lex->line) + lex->counter,
			(ft_strlen(lex->line) + lex->counter) * sizeof(char));
	if (lex->line2 == NULL)
		errorexit("malloc error line2");
	lex->lexer = create_lexer_string(lex);
	if (!lex->lexer)
		errorexit("lex->lexer allocation failed");
	print_lexer(lex);
	return (lex);
}
