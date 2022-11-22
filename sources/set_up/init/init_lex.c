#include "../../../includes/minishell.h"

static char	*minishell_gnl_free_line(char *line)
{
	free(line);
	return (NULL);
}

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

	line = NULL;
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

int	read_input(t_lex *lex, t_env *env)
{
	if (isatty(STDIN_FILENO))
	{
		lex->line = readline("input: ");
		signal(SIGINT, SIG_IGN);
	}
	else
		lex->line = minishell_get_next_line(STDIN_FILENO);
	if (lex->line == NULL)
	{
		if (isatty(STDERR_FILENO))
		{
			free_env(env);
			rl_clear_history();
			if (lex)
				free_struct(NULL, NULL, lex);
			ft_putstr_fd("exit\n", STDERR_FILENO);
		}
		exit (g_exit_code);
	}
	else if (!lex->line[0])
		return (1);
	return (0);
}

void	init_lex_bis(t_lex *lex, t_env *env)
{
	lex->counter = lexer_count_spaces(lex);
	lex->iter = 0;
	lex->no_processes = 0;
	lex->line2 = ft_calloc((ft_strlen(lex->line) + 1)
			+ lex->counter, sizeof(char));
	if (!lex->line2)
	{
		free_struct_lex(lex);
		free_env(env);
		exit (g_exit_code);
	}
}

t_lex	*initialize_lex(t_env *env)
{
	t_lex	*lex;

	lex = ft_calloc(1, sizeof(t_lex));
	if (!lex)
		return (NULL);
	if (read_input(lex, env))
		return (free_struct_lex(lex));
	lex->line = convert_tabs_to_spaces(lex->line);
	if (!lex->line)
		return (free_struct_lex(lex));
	init_lex_bis(lex, env);
	create_line2(lex);
	lex->lexer = ft_split(lex->line2, -1);
	if (!lex->lexer || !lex->lexer[0])
		return (free_struct_lex(lex));
	lex->lexer_c = NULL;
	if (check_syntax(lex))
		return (free_struct_lex(lex));
	return (lex);
}
