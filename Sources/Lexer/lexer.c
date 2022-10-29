/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:06:11 by jmatheis          #+#    #+#             */
/*   Updated: 2022/10/29 17:55:25 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	errorexit(char *message)
{
	ft_printf("%s\n", message);
	exit(EXIT_FAILURE);
}

static void	lexer_count_spaces(char *line, int i, t_lex *lex)
{
	if (line[i] != ' ' && line[i + 1] == '|')
		lex->counter++;
	if (line[i] != ' ' && line[i] != '<'
		&& line[i + 1] == '<')
		lex->counter++;
	if (line[i] != ' ' && line[i] != '>'
		&& line[i + 1] == '>')
		lex->counter++;
	if (line[i] == '<' && line[i + 1] != '<' && line[i + 1] != ' ')
		lex->counter++;
	if (line[i] == '>' && line[i + 1] != '>' && line[i + 1] != ' ')
		lex->counter++;
}

// double quote & single quote must be handled differently
/* inserts spaces when sign & filename should be seperated
ASCII 39 = single quote*/
static void	calloc_line2_withspaces(char *line, t_lex *lex)
{
	int	i;

	i = 0;
	lex->counter = 0;
	while (line && line[i])
	{
		lexer_count_spaces(line, i, lex);
		i++;
	}
	lex->line2 = ft_calloc(ft_strlen(line) + lex->counter,
			(ft_strlen(line) + lex->counter) * sizeof(char));
	if (lex->line2 == NULL)
		errorexit("malloc error line2");
}

static void	quotings(t_lex *lex)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (lex->lexer && lex->lexer[i])
	{
		if (lex->lexer[i][0] == '"')
		{
			j = ft_strlen(lex->lexer[i]) - 1;
			// if (lex->lexer[i][j] != '"')
			// {
			// 	// INSERT SPACE
			// 	printf("DOUBLE");
			// }
		}
		i++;
	}
}
// HANDLE DOUBLE QUOTES WITH SPACES IN IT!!
// cat<<Makefile grep"hello world"| cat>>outfile
// < "Makefile" cat >outfile
// grep "a"b"" --> works for hello ab
/* takes input string and splits it into tokens*/
void	create_lexer_string(char *line, t_lex *lex)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	calloc_line2_withspaces(line, lex);
	while (line && line[i])
	{
		while ((line[i] != ' ' && line[i + 1] == '|')
			|| (line[i] != ' ' && line[i] != '<' && line[i + 1] == '<')
			|| (line[i] != ' ' && line[i] != '>' && line[i + 1] == '>')
			|| (line[i] == '<' && line[i + 1] != '<' && line[i + 1] != ' ')
			|| (line[i] == '>' && line[i + 1] != '>' && line[i + 1] != ' '))
		{
			lex->line2[j] = line[i];
			j++;
			i++;
			lex->line2[j] = ' ';
			j++;
		}
		lex->line2[j] = line[i];
		j++;
		i++;
	}
	lex->lexer = split_lexer(lex->line2, ' ');
	quotings(lex);
	print_lexer(lex);
}

// CHECKING LEXER
void	print_lexer(t_lex *lex)
{
	int	i;

	i = 0;
	while (lex->lexer[i])
	{
		printf("%s\n", lex->lexer[i]);
		i++;
	}
}
