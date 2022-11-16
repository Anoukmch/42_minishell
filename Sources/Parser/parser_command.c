#include "../../includes/minishell.h"

/*
grep "hello world" >outfile | 'my name is' > infile
*/
int	commands(t_lex *lex, t_child *child)
{
	int	j;

	j = 0;
	while (lex->lexer[lex->iter]
		&& (ft_strncmp(lex->lexer[lex->iter], "|", 2) != 0))
	{
		if ((ft_strncmp(lex->lexer[lex->iter], "<", 2) == 0
				|| ft_strncmp(lex->lexer[lex->iter], "<<", 3) == 0
				|| ft_strncmp(lex->lexer[lex->iter], ">", 2) == 0
				|| ft_strncmp(lex->lexer[lex->iter], ">>", 3) == 0))
			lex->iter += 2;
		else
		{
			child->parser_cmd[j] = ft_strdup(lex->lexer[lex->iter]);
			if (!child->parser_cmd[j])
				return (1);
			j++;
			lex->iter++;
		}
	}
	child->parser_cmd[j] = NULL;
	return (0);
}

int	parse_commands(t_lex *lex, t_child **child)
{
	int	k;

	k = 0;
	lex->iter = 0;
	while (child[k])
	{
		if (commands(lex, child[k]))
			return (1);
		lex->iter++;
		k++;
	}
	return (0);
}
