#include "../../includes/minishell.h"

static int	count_substr_len(const char *s, char c, int len)
{
	int	i;

	i = 0;
	while (s[len] && s[len] != c)
	{
		i++;
		len++;
	}
	return (i);
}

static char	**check_null_string(int nb_of_strs, char	**arr)
{
	int		string_index;

	string_index = 0;
	while (string_index < nb_of_strs)
	{
		free(arr[string_index]);
		string_index++;
	}
	free(arr);
	return (NULL);
}

char	**ft_split_command(char **arr, int nb_of_strs, char const *s, char c)
{
	size_t	i;
	int		string_index;

	i = 0;
	string_index = 0;
	if (s == NULL)
		return (NULL);
	while (i < ft_strlen(s) && string_index < (nb_of_strs))
	{
		while (s[i] == c)
			i++;
		arr[string_index] = ft_substr(s, i, count_substr_len(s, c, i));
		if (arr[string_index] == NULL)
			return (check_null_string(nb_of_strs, arr));
		string_index++;
		i += count_substr_len(s, c, i);
	}
	arr[string_index] = NULL;
	return (arr);
}

int	allocate_parse_cmd(t_lex *lex, t_child *child, int *j, int *count)
{
	*j = *count;
	free_array(child->parser_cmd);
	child->parser_cmd = ft_calloc(child->no_cmd_opt
			+ (*count) + 1, sizeof(char *));
	if (!child->parser_cmd)
		return (1);
	child->parser_cmd = ft_split_command(child->parser_cmd,
			(*count + 1), lex->lexer[lex->iter], -3);
	if (!child->parser_cmd)
		return (1);
	return (0);
}

int	check_first_command(t_lex *lex, t_child *child, int *j)
{
	char	quote;
	int		count;
	int		i;

	quote = '\0';
	count = 0;
	i = 0;
	while (lex->lexer[lex->iter][i])
	{
		skipquotes(&quote, lex->lexer[lex->iter][i]);
		if (quote == '\0' && lex->lexer[lex->iter][i] == ' ')
		{
			lex->lexer[lex->iter][i] = -3;
			count++;
		}
		i++;
	}
	if (count == 0)
		return (2);
	else if (allocate_parse_cmd(lex, child, j, &count))
		return (1);
	return (0);
}
