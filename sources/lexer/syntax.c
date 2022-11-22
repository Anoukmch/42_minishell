/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:24:33 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/22 15:24:38 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	return_status_syntaxerror(char *arg, int status)
{
	ft_putstr_fd("syntax error near unexpected token '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("'\n", 2);
	return (status);
}

int	redirections(t_lex *lex, int i)
{
	if ((!ft_strcmp(lex->lexer[i], ">")
			|| !ft_strcmp(lex->lexer[i], "<")
			|| !ft_strcmp(lex->lexer[i], ">>")
			|| !ft_strcmp(lex->lexer[i], "<<"))
		&& (!lex->lexer[i + 1] || !ft_strcmp(lex->lexer[i + 1], ">")
			|| !ft_strcmp(lex->lexer[i + 1], "<")
			|| !ft_strcmp(lex->lexer[i + 1], ">>")
			|| !ft_strcmp(lex->lexer[i + 1], "<<")))
		return (1);
	if (!ft_strncmp(lex->lexer[i], ">>>", 3)
		|| !ft_strncmp(lex->lexer[i], "<<<", 3))
		return (1);
	return (0);
}

void	set_exitcode(char *str)
{
	if (!ft_strcmp(str, "."))
		g_exit_code = 127;
	else
		g_exit_code = 2;
}

int	check_syntax(t_lex *lex)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (lex->lexer[i])
	{
		if (!ft_strcmp(lex->lexer[0], "|") || (!ft_strcmp(lex->lexer[i], "|")
				&& !ft_strcmp(lex->lexer[i + 1], "|")))
		{
			g_exit_code = 2;
			return (return_status_syntaxerror(lex->lexer[i], 2));
		}
		else if (!ft_strcmp(lex->lexer[i], "|"))
			j = 0;
		else if (((i == 0 || j == 1) && (!ft_strcmp(lex->lexer[i], "|")
					|| !ft_strcmp(lex->lexer[i], "."))) || redirections(lex, i))
		{
			set_exitcode(lex->lexer[i]);
			return (return_status_syntaxerror(lex->lexer[i], 2));
		}
		i++;
	}
	return (0);
}
