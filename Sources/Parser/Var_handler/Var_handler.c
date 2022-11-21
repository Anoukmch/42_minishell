#include "../../../includes/minishell.h"

int	var_handler(t_lex *lex, t_env *env)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (lex->lexer[i])
	{
		if (ft_strchr(lex->lexer[i], -2) != NULL)
		{
			lex->lexer[i] = handle_var(lex->lexer[i], env);
			if (!lex->lexer[i])
				return (1);
		}
		i++;
	}
	lex->lexer = rebuild_lex(lex);
	return (0);
}
