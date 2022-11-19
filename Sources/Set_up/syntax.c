#include "../../includes/minishell.h"

int	double_redirection(t_lex *lex, int i)
{
	if ((!ft_strcmp(lex->lexer[i], ">")
			|| !ft_strcmp(lex->lexer[i], "<")
			|| !ft_strcmp(lex->lexer[i], ">>")
			|| !ft_strcmp(lex->lexer[i], "<<"))
		&& (!lex->lexer[i + 1] || !ft_strcmp(lex->lexer[i + 1], ">")
			|| !ft_strcmp(lex->lexer[i + 1], "<")
			|| !ft_strcmp(lex->lexer[i + 1], ">>")
			|| !ft_strcmp(lex->lexer[i + 1], "<<")))
	{
		g_exit_code = 2;
		return (1);
	}
	return (0);
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
			return (perror_return_status("syntax error", 2));
		}
		else if (!ft_strcmp(lex->lexer[i], "|"))
			j = 0;
		else if (((i == 0 || j == 1) && (!ft_strcmp(lex->lexer[i], "|")
					|| !ft_strcmp(lex->lexer[i], ".")))
			|| double_redirection(lex, i))
		{
			g_exit_code = 2;
			return (perror_return_status("syntax error", 2));
		}
		i++;
	}
	return (0);
}
