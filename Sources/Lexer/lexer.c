/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:06:11 by jmatheis          #+#    #+#             */
/*   Updated: 2022/10/26 17:07:55 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	errorexit(char *message)
{
	ft_printf("%s\n", message);
	exit(EXIT_FAILURE);
}

// double quote & single quote must be handled differently
/* inserts spaces when sign & filename should be seperated
ASCII 39 = single quote*/
static void calloc_line2_withspaces(char *line, t_lex *lex)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while(line[i])
	{
		if ((line[i] == '<' || line[i] == '>'
			|| line[i] == '"' || line[i] == 39)
			&& (ft_isalpha(line[i + 1]) == 0
				|| ft_isdigit(line[i + 1]) == 0))
			count++;
		i++;
	}
	lex->line2 = ft_calloc(ft_strlen(line) + count,
			(ft_strlen(line) + count) * sizeof(char));
	if (lex->line2 == NULL)
		errorexit("malloc error line2");
}

// < "Makefile" cat >outfile
/* takes input string and splits it into tokens*/
void	create_lexer_string(char *line, t_lex *lex)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	calloc_line2_withspaces(line, lex);
	while (line[i])
	{
		if ((line[i] == '<' || line[i] == '>')
			&& (ft_isalpha(line[i + 1]) == 0
				|| ft_isdigit(line[i + 1]) == 0))
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
	// HANDLE DOUBLE QUOTES WITH SPACES IN IT!!
	lex->lexer = ft_split(lex->line2, ' ');
	// CHECK LEXER BELOW
	i = 0;
	while (lex->lexer[i])
	{
		printf("%s\n", lex->lexer[i]);
		i++;
	}
}


// void	create_lexer_string(char *line, t_par *par)
// {
// 	t_lex *p;
// 	p = par->lex;
// 	p->lexer
// }
