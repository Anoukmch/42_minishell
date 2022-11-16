
#include "../../includes/minishell.h"

int	check_syntax(t_lex *lex)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (lex->lexer[i])
	{
		if (!ft_strcmp(lex->lexer[0], "|"))
		{
			g_exit_code = 2;
			return (perror_return_status("syntax error", 2));
		}
		else if (!ft_strcmp(lex->lexer[i], "|")
			&& (!ft_strcmp(lex->lexer[i + 1], "|")
				|| !lex->lexer[i + 1]))
		{
			g_exit_code = 2;
			return (perror_return_status("syntax error", 2));
		}
		else if (!ft_strcmp(lex->lexer[i], "|"))
			j = 0;
		else if ((i == 0 || j == 1) && (!ft_strcmp(lex->lexer[i], "|")
				|| !ft_strcmp(lex->lexer[i], ".")))
		{
			g_exit_code = 2;
			return (perror_return_status("syntax error", 2));
		}
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
			return (perror_return_status("syntax error", 2));
		}
		i++;
	}
	return (0);
}
