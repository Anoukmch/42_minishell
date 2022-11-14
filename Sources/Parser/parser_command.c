

#include "../../includes/minishell.h"

/*
grep "hello world" >outfile | 'my name is' > infile
*/
int	commands(t_lex *lex, t_child **child, int k)
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
			// lex->lexer[lex->iter] = mark_quotes(lex->lexer[lex->iter]);
			// child[k]->parser_cmd[j] = delete_quotes(lex->lexer[lex->iter]);
			child[k]->parser_cmd[j] = ft_strdup(lex->lexer[lex->iter]);
			if (!child[k]->parser_cmd[j])
				return (1);
			j++;
			lex->iter++;
		}
	}
	child[k]->parser_cmd[j] = NULL;
	return (0);
}

int	parse_commands(t_lex *lex, t_child **child)
{
	int	k;

	k = 0;
	lex->iter = 0;
	while (k < lex->no_processes)
	{
		if (commands(lex, child, k))
			return (1);
		lex->iter++;
		k++;
	}
	return (0);
}
