#include "../../../includes/minishell.h"

int	mark_variables(char *str, char *str_before)
{
	char	quote;
	int		i;

	i = 0;
	quote = '\0';
	while (str[i])
	{
		if (quote == '\0' && str[i] == '\'')
			quote = '\'';
		else if (quote == '\0' && str[i] == '\"')
			quote = '\"';
		else if (quote == '\'' && str[i] == '\'')
			quote = '\0';
		else if (quote == '\"' && str[i] == '\"')
			quote = '\0';
		else if ((quote == '\"' || quote == '\0')
			&& str[i] == '$' && ft_strcmp(str_before, "<<"))
			str[i] = -2;
		i++;
	}
	if (quote == '\'' || quote == '\"')
		return (perror_return_status("Unclosed pair of quotes", 1));
	return (0);
}

int	check_dollarsign(char *str)
{
	char	tmp[4];
	char	*replace;
	int		i;

	tmp[0] = '\"';
	tmp[1] = -2;
	tmp[2] = '\"';
	tmp[3] = '\0';
	replace = ft_strnstr(str, tmp, ft_strlen(str));
	while (ft_strchr(str, -2) && replace)
	{
		replace[1] = '$';
		replace = ft_strnstr(str, tmp, ft_strlen(str));
	}
	i = 0;
	while (str[i])
	{
		if ((str[i] == -2 && (str[i + 1] == -2))
			|| (str[i] == -2 && !ft_isalnum(str[i + 1])
				&& str[i + 1] != '_' && str[i + 1] != '?'
				&& str[i + 1] != '\"' && str[i + 1] != '\''))
			str[i] = '$';
		i++;
	}
	return (0);
}

int	delete_marked_dollarsign(t_lex *lex, int no, int *count)
{
	char	*new_lex;
	int		i;

	i = 0;
	new_lex = NULL;
	new_lex = ft_calloc((ft_strlen(lex->lexer[no]) + 1)
			- (*count), sizeof(char));
	if (!new_lex)
		return (1);
	*count = 0;
	while (lex->lexer[no][i])
	{
		if (lex->lexer[no][i] == -3)
			i++;
		else
		{
			new_lex[*count] = lex->lexer[no][i];
			(*count)++;
			i++;
		}
	}
	new_lex[*count] = '\0';
	free (lex->lexer[no]);
	lex->lexer[no] = new_lex;
	return (0);
}

int	quotes_after_dollarsign(t_lex *lex, int no)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	quote = 's';
	while (lex->lexer[no][i])
	{
		if (quote == '\"' && lex->lexer[no][i] == -2
			&& lex->lexer[no][i + 1] == '\"')
			lex->lexer[no][i] = '$';
		skipquotes(&quote, lex->lexer[no][i]);
		if (quote == '\0' && lex->lexer[no][i] == -2
			&& (lex->lexer[no][i + 1] == '\'' || lex->lexer[no][i + 1] == '\"'))
		{
			lex->lexer[no][i] = -3;
			count++;
		}
		i++;
	}
	if (delete_marked_dollarsign(lex, no, &count))
		return (1);
	return (0);
}
