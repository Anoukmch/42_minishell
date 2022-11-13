

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

void	skipquotes(char *quote, char lex)
{
	if (*quote == '\0' && lex == '\'')
		*quote = '\'';
	else if (*quote == '\0' && lex == '\"')
		*quote = '\"';
	else if (*quote == '\'' && lex == '\'')
		*quote = '\0';
	else if (*quote == '\"' && lex == '\"')
		*quote = '\0';
}

int	lexer_count_spaces(t_lex *lex)
{
	int		i;
	char	quote;
	bool	notdouble;

	quote = '\0';
	i = 0;
	lex->counter = 0;
	notdouble = 0;
	while (lex->line[i] != '\0')
	{
		if (quote == '\0')
		{
			if (lex->line[i - 1] == '|' && lex->line[i] != ' ')
			{
				notdouble = 1;
				lex->counter++;
			}
			else if (lex->line[i - 1] == '<'
				&& lex->line[i] != '<' && lex->line[i] != ' ')
			{
				notdouble = 1;
				lex->counter++;
			}
			else if (lex->line[i - 1] == '>'
				&& lex->line[i] != '>' && lex->line[i] != ' ')
			{
				notdouble = 1;
				lex->counter++;
			}
		}
		skipquotes(&quote, lex->line[i]);
		if (notdouble != 1 && quote == '\0')
		{
			if (lex->line[i] == '|' && lex->line[i - 1] != ' ')
				lex->counter++;
			else if (lex->line[i] == '<'
				&& lex->line[i - 1] != '<' && lex->line[i - 1] != ' ')
				lex->counter++;
			else if (lex->line[i] == '>'
				&& lex->line[i - 1] != '>' && lex->line[i - 1] != ' ')
				lex->counter++;
		}
		notdouble = 0;
		i++;
	}
	return (lex->counter);
}

void	create_line2(t_lex *lex)
{
	int		i;
	int		j;
	int		count;
	char	quote;
	bool	notdouble;

	quote = '\0';
	i = 0;
	j = 0;
	count = 0;
	notdouble = 0;
	while (lex->line[i] != '\0')
	{
		if (quote == '\0')
		{
			if (lex->line[i - 1] == '|' && lex->line[i] != ' ')
			{
				notdouble = 1;
				lex->line2[j++] = -1;
			}
			else if (lex->line[i - 1] == '<'
				&& lex->line[i] != '<' && lex->line[i] != ' ')
			{
				notdouble = 1;
				lex->line2[j++] = -1;
			}
			else if (lex->line[i - 1] == '>'
				&& lex->line[i] != '>' && lex->line[i] != ' ')
			{
				notdouble = 1;
				lex->line2[j++] = -1;
			}
		}
		skipquotes(&quote, lex->line[i]);
		if (notdouble != 1 && quote == '\0')
		{
			if (lex->line[i] == '|' && lex->line[i - 1] != ' ')
				lex->line2[j++] = -1;
			else if (lex->line[i] == '<'
				&& lex->line[i - 1] != '<' && lex->line[i - 1] != ' ')
				lex->line2[j++] = -1;
			else if (lex->line[i] == '>'
				&& lex->line[i - 1] != '>' && lex->line[i - 1] != ' ')
				lex->line2[j++] = -1;
		}
		if (quote == '\0' && lex->line[i] == ' ')
			lex->line2[j] = -1;
		else
			lex->line2[j] = lex->line[i];
		notdouble = 0;
		j++;
		i++;
	}
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
	lex->counter = lexer_count_spaces(lex);
	lex->iter = 0;
	lex->no_processes = 0;
	lex->line2 = ft_calloc(ft_strlen(lex->line) + lex->counter, sizeof(char));
	if (lex->line2 == NULL)
		errorexit("malloc error line2");
	create_line2(lex);
	lex->lexer = ft_split(lex->line2, -1);
	if (!lex->lexer)
		errorexit("lex->lexer allocation failed");
	free_doublepointer(ft_split(lex->line2, -1));
	free(lex->line2);
	// print_lexer(lex);
	return (lex);
}
