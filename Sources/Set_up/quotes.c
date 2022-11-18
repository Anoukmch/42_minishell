#include "../../includes/minishell.h"

// int	quote_start_and_end(char str, char *quote)
// {

// }

// 1. handle varaibles, then quotes
// INT FUNCTION
// Marking $ signs outside of quotes & in double quotes with -2
int	mark_quotes_cmds_and_outdir(char *str)
{
	char	quote;
	int		i;

	i = 0;
	quote = '\0';
	while (str[i])
	{
		if (quote == '\0' && str[i] == '\'')
		{
			quote = '\'';
			str[i] = -1;
		}
		else if (quote == '\0' && str[i] == '\"')
		{
			quote = '\"';
			str[i] = -1;
		}
		else if (quote == '\'' && str[i] == '\'')
		{
			quote = '\0';
			str[i] = -1;
		}
		else if (quote == '\"' && str[i] == '\"')
		{
			quote = '\0';
			str[i] = -1;
		}
		i++;
	}
	if (quote == '\'' || quote == '\"')
		return (perror_return("Unclosed pair of quotes"));
	return (0);
}

char	*delete_quotes_cmds_and_outdir(char *str)
{
	int		i;
	int		count;
	char	*final;

	i = 0;
	count = 0;
	final = NULL;
	while (str[i])
	{
		if (str[i] == -1)
			count++;
		i++;
	}
	final = malloc((ft_strlen(str) - count) * sizeof(char));
	if (final == NULL)
		return (NULL);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != -1)
		{
			final[count] = str[i];
			count++;
		}
		i++;
	}
	final[count] = '\0';
	free(str);
	return (final);
}

char	*delete_quotes(char *str)
{
	int		i;
	int		count;
	char	*final;

	i = 0;
	count = 0;
	final = NULL;
	while (str[i])
	{
		if (str[i] == -1)
			count++;
		i++;
	}
	final = malloc((ft_strlen(str) - count) * sizeof(char));
	if (final == NULL)
		return (NULL);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != -1)
		{
			final[count] = str[i];
			count++;
		}
		i++;
	}
	final[count] = '\0';
	free(str);
	return (final);
}

char	*delete_quotes_indir(t_child *child, t_lex *lex)
{
	int		i;
	int		count;
	char	*final;

	i = 0;
	count = 0;
	final = NULL;
	while (lex->lexer[lex->counter][i])
	{
		if (lex->lexer[lex->counter][i] == -1)
			count++;
		i++;
	}
	final = malloc((ft_strlen(lex->lexer[lex->counter]) - count) * sizeof(char));
	if (final == NULL)
		return (NULL);
	i = 0;
	count = 0;
	while (lex->lexer[lex->counter][i])
	{
		if (lex->lexer[lex->counter][i] != -1)
		{
			final[count] = lex->lexer[lex->counter][i];
			count++;
		}
		else
		{
			if (lex->counter != 0 && !ft_strcmp(lex->lexer[lex->counter - 1], "<<")
				&& ft_strchr(lex->lexer[lex->counter], -1))
				child->heredoc_quotes = 1;
		}
		i++;
	}
	final[count] = '\0';
	free(lex->lexer[lex->counter]);
	return (final);
}