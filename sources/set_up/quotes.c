/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:26:24 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/22 15:26:29 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	mark_quotechar(char str, char *quote)
{
	if (str == '\'')
		*quote = '\'';
	else if (str == '\"')
		*quote = '\"';
}

int	mark_quotes_cmds_and_outdir(char *str)
{
	char	quote;
	int		i;

	i = 0;
	quote = '\0';
	while (str[i])
	{
		if ((quote == '\0' && str[i] == '\'')
			|| (quote == '\0' && str[i] == '\"'))
		{
			mark_quotechar(str[i], &quote);
			str[i] = -1;
		}
		else if ((quote == '\'' && str[i] == '\'')
			|| (quote == '\"' && str[i] == '\"'))
		{
			quote = '\0';
			str[i] = -1;
		}
		i++;
	}
	if (quote == '\'' || quote == '\"')
		return (perror_return_status(NULL, "Unclosed pair of quotes", 1));
	return (0);
}

int	count_deletingquotes(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == -1)
			count++;
		i++;
	}
	return (count);
}

char	*delete_quotes_cmds_and_outdir(char *str)
{
	int		i;
	int		count;
	char	*final;

	final = NULL;
	count = count_deletingquotes(str);
	final = malloc(((ft_strlen(str) + 1) - count) * sizeof(char));
	if (final == NULL)
		return (NULL);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != -1)
		{
			final[count] = str[i];
			count++;
		}
		i++;
	}
	final[count] = '\0';
	free(str);
	return (final);
}

char	*delete_quotes_indir(t_child *child, t_lex *lex)
{
	int		i;
	int		count;
	char	*final;

	final = NULL;
	count = count_deletingquotes(lex->lexer[lex->counter]);
	final = malloc((ft_strlen(lex->lexer[lex->counter]) + 1) - count
			* sizeof(char));
	if (final == NULL)
		return (NULL);
	i = 0;
	count = 0;
	while (lex->lexer[lex->counter][i])
	{
		if (lex->lexer[lex->counter][i] != -1)
			final[count++] = lex->lexer[lex->counter][i];
		else if (lex->counter != 0 && ft_strchr(lex->lexer[lex->counter], -1)
			&& !ft_strcmp(lex->lexer[lex->counter - 1], "<<"))
				child->heredoc_quotes = 1;
		i++;
	}
	final[count] = '\0';
	free(lex->lexer[lex->counter]);
	return (final);
}
