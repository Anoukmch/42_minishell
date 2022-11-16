#include "../../includes/minishell.h"

static char	*minishell_gnl_free_line(char *line);

// ***** FOR MINISHELL TESTER *****
static char	*str_append_chr(char *str, char append)
{
	char	*new_str;
	int		i;

	if (str == NULL)
		return (NULL);
	new_str = malloc(ft_strlen(str) + 2);
	if (new_str != NULL)
	{
		i = 0;
		while (str[i])
		{
			new_str[i] = str[i];
			i++;
		}
		new_str[i] = append;
		new_str[i + 1] = '\0';
	}
	free(str);
	return (new_str);
}

char	*minishell_get_next_line(int fd)
{
	char	*line;
	char	buffer;
	int		check;

	line = ft_strdup("");
	if (line == NULL)
		return (NULL);
	check = read(fd, &buffer, 1);
	if (check == -1 || check == 0)
		return (minishell_gnl_free_line(line));
	while (check > 0)
	{
		if (buffer != '\n')
			line = str_append_chr(line, buffer);
		if (line == NULL)
			return (NULL);
		if (buffer == '\n')
			return (line);
		check = read(fd, &buffer, 1);
	}
	if (check == -1)
		return (minishell_gnl_free_line(line));
	return (line);
}

static char	*minishell_gnl_free_line(char *line)
{
	free(line);
	return (NULL);
}

// OUR CODE

//  The Ctrl-d (^D) character will send an end of file signal
//	CTRL-D referrs to STDERR??
t_lex	*initialize_lex(void)
{
	t_lex	*lex;

	lex = ft_calloc(1, sizeof(t_lex));
	if (!lex)
		return (NULL);
	if (isatty(STDIN_FILENO))// ***** FOR MINISHELL TESTER *****
		lex->line = readline("input: "); // lex->line = readline("input: "); // comment out for MINISHELL TESTER
	else
		lex->line = minishell_get_next_line(STDIN_FILENO);
	if (lex->line == NULL)
	{
		if (isatty(STDERR_FILENO))
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			exit (0);
		}
		return (NULL);
	}
	else if (!lex->line[0])
		return (NULL);
	lex->line = convert_tabs_to_spaces(lex->line);
	lex->counter = lexer_count_spaces(lex);
	lex->iter = 0;
	lex->no_processes = 0;
	lex->line2 = ft_calloc((ft_strlen(lex->line)
		+ lex->counter + 1), sizeof(char));
	if (!lex->line2)
		return (NULL);
	create_line2(lex);
	lex->lexer = ft_split(lex->line2, -1);
	if (!lex->lexer)
		return (NULL);
	return (lex);
}
