#include "../../../includes/minishell.h"

int	nbr_dollar_sign_hd(char *lex_string)
{
	int	size;
	int	count;

	count = 0;
	size = ft_strlen(lex_string) - 1;
	while (size >= 0)
	{
		if (lex_string[size] == '$')
			count++;
		size--;
	}
	return (count);
}
