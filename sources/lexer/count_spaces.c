#include "../../includes/minishell.h"

// static void	spaces_before_quotes(t_lex *lex, bool *notdouble, int i)
// {
// 	if (lex->line[i - 1] == '|' && lex->line[i] != ' ')
// 	{
// 		(*notdouble) = 1;
// 		lex->counter++;
// 	}
// 	else if (lex->line[i - 1] == '<'
// 		&& lex->line[i] != '<' && lex->line[i] != ' ')
// 	{
// 		(*notdouble) = 1;
// 		lex->counter++;
// 	}
// 	else if (lex->line[i - 1] == '>'
// 		&& lex->line[i] != '>' && lex->line[i] != ' ')
// 	{
// 		(*notdouble) = 1;
// 		lex->counter++;
// 	}
// }

// static void	spaces_after_quotes(t_lex *lex, int i)
// {
// 	if (lex->line[i] == '|' && lex->line[i - 1] != ' ')
// 		lex->counter++;
// 	else if (lex->line[i] == '<'
// 		&& lex->line[i - 1] != '<' && lex->line[i - 1] != ' ')
// 		lex->counter++;
// 	else if (lex->line[i] == '>'
// 		&& lex->line[i - 1] != '>' && lex->line[i - 1] != ' ')
// 		lex->counter++;
// }

static void	spaces_before_quotes(t_lex *lex, int i)
{
	if (lex->line[i + 1])
	{
		if (lex->line[i] == '|' && lex->line[i + 1] != ' ')
			lex->counter++;
		else if (lex->line[i] == '<'
			&& lex->line[i + 1] != '<' && lex->line[i + 1] != ' ')
			lex->counter++;
		else if (lex->line[i] == '>'
			&& lex->line[i + 1] != '>' && lex->line[i + 1] != ' ')
			lex->counter++;
		else if (lex->line[i + 1] == '|' && lex->line[i] != ' ')
			lex->counter++;
		else if (lex->line[i + 1] == '<'
			&& lex->line[i] != '<' && lex->line[i] != ' ')
			lex->counter++;
		else if (lex->line[i + 1] == '>'
			&& lex->line[i] != '>' && lex->line[i] != ' ')
			lex->counter++;
	}
}

// static void	spaces_after_quotes(t_lex *lex, int i)
// {
// 	if (lex->line[i + 1] == '|' && lex->line[i] != ' ')
// 		lex->counter++;
// 	else if (lex->line[i + 1] == '<'
// 		&& lex->line[i] != '<' && lex->line[i] != ' ')
// 		lex->counter++;
// 	else if (lex->line[i + 1] == '>'
// 		&& lex->line[i] != '>' && lex->line[i] != ' ')
// 		lex->counter++;
// }

// int	lexer_count_spaces(t_lex *lex)
// {
// 	int		i;
// 	char	quote;
// 	bool	notdouble;

// 	quote = 's';
// 	i = 0;
// 	lex->counter = 0;
// 	notdouble = 0;
// 	while (lex->line[i] != '\0')
// 	{
// 		printf("LEX->COUNTER: %d\n", lex->counter);
// 		if (quote == '\0')
// 			spaces_before_quotes(lex, &notdouble, i);
// 		printf("LEX->COUNTER: %d\n", lex->counter);
// 		skipquotes(&quote, lex->line[i]);
// 		if (notdouble != 1 && quote == '\0')
// 		{
// 			printf("LEX->COUNTER: %d\n", lex->counter);
// 			spaces_after_quotes(lex, i);
// 		}
// 		notdouble = 0;
// 		i++;
// 	}
// 	return (lex->counter);
// }

int	lexer_count_spaces(t_lex *lex)
{
	int		i;
	char	quote;

	quote = 's';
	i = 0;
	lex->counter = 0;
	while (lex->line[i] != '\0')
	{
		skipquotes(&quote, lex->line[i]);
		if (quote == '\0')
			spaces_before_quotes(lex, i);
		i++;
	}
	return (lex->counter);
}
