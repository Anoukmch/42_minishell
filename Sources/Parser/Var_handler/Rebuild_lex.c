#include "../../../includes/minishell.h"

int	size_new_lex(t_lex *lex, int *i)
{
	int	count;

	count = 0;
	while (lex->lexer[*i])
	{
		if (!ft_strcmp(lex->lexer[*i], "\0"))
			count++;
		(*i)++;
	}
	return (count);
}

void	fill_new_lex(t_lex *lex)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (lex->lexer[i])
	{
		if (ft_strcmp(lex->lexer[i], "\0"))
		{
			lex->lexer_c[j] = ft_strdup(lex->lexer[i]);
			if (!lex->lexer_c[j])
				return ;
			j++;
		}
		i++;
	}
	lex->lexer_c[j] = NULL;
}

char	**rebuild_lex(t_lex *lex)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = size_new_lex(lex, &i);
	lex->lexer_c = ft_calloc((i + 1 - count), sizeof(char *));
	if (!lex->lexer_c)
		return (NULL);
	fill_new_lex(lex);
	free_array(lex->lexer);
	lex->lexer = lex->lexer_c;
	return (lex->lexer);
}
