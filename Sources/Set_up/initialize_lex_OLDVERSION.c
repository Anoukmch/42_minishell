/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_lex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:20:11 by amechain          #+#    #+#             */
/*   Updated: 2022/11/13 12:01:12 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// ***** FOR MINISHELL TESTER *****
// static char	*str_append_chr(char *str, char append)
// {
// 	char	*new_str;
// 	int		i;

// 	if (str == NULL)
// 		return (NULL);
// 	new_str = malloc(ft_strlen(str) + 2);
// 	if (new_str != NULL)
// 	{
// 		i = 0;
// 		while (str[i])
// 		{
// 			new_str[i] = str[i];
// 			i++;
// 		}
// 		new_str[i] = append;
// 		new_str[i + 1] = '\0';
// 	}
// 	free(str);
// 	return (new_str);
// }

// static char	*minishell_gnl_free_line(char *line);

// char	*minishell_get_next_line(int fd)
// {
// 	char	*line;
// 	char	buffer;
// 	int		check;

// 	line = ft_strdup("");
// 	if (line == NULL)
// 		return (NULL);
// 	check = read(fd, &buffer, 1);
// 	if (check == -1 || check == 0)
// 		return (minishell_gnl_free_line(line));
// 	while (check > 0)
// 	{
// 		if (buffer != '\n')
// 			line = str_append_chr(line, buffer);
// 		if (line == NULL)
// 			return (NULL);
// 		if (buffer == '\n')
// 			return (line);
// 		check = read(fd, &buffer, 1);
// 	}
// 	if (check == -1)
// 		return (minishell_gnl_free_line(line));
// 	return (line);
// }

// static char	*minishell_gnl_free_line(char *line)
// {
// 	free(line);
// 	return (NULL);
// }

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
				&& lex->line[i] != '"' && lex->line[i] != 39
				&& lex->line[i + 1] == '<') || (lex->line[i] != ' '
				&& lex->line[i] != '>' && lex->line[i + 1] == '>'
				&& lex->line[i] != '"' && lex->line[i] != 39)
			|| (lex->line[i] == '<' && lex->line[i + 1] != '<'
				&& lex->line[i + 1] != ' ' && lex->line[i + 1] != '"' && lex->line[i + 1] != 39)
				|| (lex->line[i] == '>'
				&& lex->line[i + 1] != '>' && lex->line[i + 1] != ' '
				&& lex->line[i + 1] != '"' && lex->line[i + 1] != 39))
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
	// ***** FOR MINISHELL TESTER *****
	// if (isatty(STDIN_FILENO))
	// 	lex->line = readline("input: ");
	// else
	// 	lex->line = minishell_get_next_line(STDIN_FILENO);
	lex->line = readline("input: "); // comment out for MINISHELL TESTER
	if (lex->line == NULL)
		errorexit("check initializiation of lex->line");
	else if (!lex->line[0])
		return (lex);
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
	exit (0); //CHECKING LEXER
	return (lex);
}
