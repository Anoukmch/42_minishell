#include "../../includes/minishell.h"

void	skipquotes(char *quote, char lex)
{
	if ((*quote == '\0' || *quote == 's') && lex == '\'')
		*quote = '\'';
	else if ((*quote == '\0' || *quote == 's') && lex == '\"')
		*quote = '\"';
	else if (*quote == 's')
		*quote = '\0';
	else if (*quote == '\'' && lex == '\'')
		*quote = '\0';
	else if (*quote == '\"' && lex == '\"')
		*quote = '\0';
}

char	*convert_tabs_to_spaces(char *str)
{
	char	quote;
	int		i;

	quote = 's';
	i = 0;
	while (str[i] != '\0')
	{
		skipquotes(&quote, str[i]);
		if (quote == '\0')
		{
			if (str[i] == '\t' || str[i] == '\n')
			{
				while (str[i] == '\t' || str[i] == '\n')
					str[i++] = ' ';
			}
		}
		i++;
	}
	return (str);
}
