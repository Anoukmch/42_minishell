#include "../../includes/minishell.h"

static void	check_before_quotes(t_lex *lex, int *j, bool *notdouble, int i)
{
	if (lex->line[i - 1] == '|' && lex->line[i] != ' ')
	{
		(*notdouble) = 1;
		lex->line2[(*j)++] = -1;
	}
	else if (lex->line[i - 1] == '<'
		&& lex->line[i] != '<' && lex->line[i] != ' ')
	{
		(*notdouble) = 1;
		lex->line2[(*j)++] = -1;
	}
	else if (lex->line[i - 1] == '>'
		&& lex->line[i] != '>' && lex->line[i] != ' ')
	{
		(*notdouble) = 1;
		lex->line2[(*j)++] = -1;
	}
}

static void	check_after_quotes(t_lex *lex, int *j, int i)
{
	if (lex->line[i] == '|' && lex->line[i - 1] != ' ')
		lex->line2[(*j)++] = -1;
	else if (lex->line[i] == '<'
		&& lex->line[i - 1] != '<' && lex->line[i - 1] != ' ')
		lex->line2[(*j)++] = -1;
	else if (lex->line[i] == '>'
		&& lex->line[i - 1] != '>' && lex->line[i - 1] != ' ')
		lex->line2[(*j)++] = -1;
}

void	create_line2(t_lex *lex)
{
	int		i;
	int		j;
	char	quote;
	bool	notdouble;

	quote = 's';
	i = 0;
	j = 0;
	notdouble = 0;
	while (lex->line[i] != '\0')
	{
		if (quote == '\0')
			check_before_quotes(lex, &j, &notdouble, i);
		skipquotes(&quote, lex->line[i]);
		if (notdouble != 1 && quote == '\0')
			check_after_quotes(lex, &j, i);
		if (quote == '\0' && lex->line[i] == ' ')
			lex->line2[j] = -1;
		else
			lex->line2[j] = lex->line[i];
		notdouble = 0;
		j++;
		i++;
	}
}
