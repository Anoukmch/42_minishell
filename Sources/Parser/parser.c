
#include "../../includes/minishell.h"

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
		else if ((quote == '\"' || quote == '\0') && str[i] == '$' && ft_strcmp(str_before, "<<"))
			str[i] = -2;
		i++;
	}
	if (quote == '\'' || quote == '\"')
		return (perror_return_status("Unclosed pair of quotes", 1));
	return (0);
}

int	check_dollarsign(char *str)
{
	char tmp[4];
	char *replace;
	int	i;

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
		if (str[i] == -2 && (str[i + 1] == -2 || !str[i + 1]))
			str[i] = '$';
		i++;
	}
	return (0);
}

int	quotes_after_dollarsign(t_lex *lex, int no)
{
	int	i;
	int	count;
	char *new_lex;

	i = 0;
	count = 0;
	new_lex = NULL;
	while (lex->lexer[no][i])
	{
		if (lex->lexer[no][i] == -2 && (lex->lexer[no][i + 1] == '\'' || lex->lexer[no][i + 1] == '\"'))
		{
			lex->lexer[no][i] = -3;
			count++;
		}
		i++;
	}
	new_lex = ft_calloc((ft_strlen(lex->lexer[no]) + 1) - count, sizeof(char));
	if (!new_lex)
		return (1);
	i = 0;
	count = 0;
	while (lex->lexer[no][i])
	{
		if (lex->lexer[no][i] == -3)
			i++;
		else
		{
			new_lex[count] = lex->lexer[no][i];
			count++;
			i++;
		}
	}
	new_lex[count] = '\0';
	free (lex->lexer[no]);
	lex->lexer[no] = new_lex;
	return (0);
}

int	parser(t_lex *lex, t_child	**child, t_env	*env)
{
	int	i;
	int	k;
	int	z;

	i = 0;
	k = 0;
	z = 0;
	// MARK VARIABLES AS -2
  	if (!lex->line[0])
    	return (1);
	while (lex->lexer[i])
	{
		if (i > 0)
		{
			if (mark_variables(lex->lexer[i], lex->lexer[i - 1]))
				return (1);
		}
		else
		{
			if (mark_variables(lex->lexer[i], NULL))
				return (1);			
		}
		if (check_dollarsign(lex->lexer[i]))
			return (1);
		if (quotes_after_dollarsign(lex, i))
			return (1);
		// EXPAND VARIABLES IF FOUND IN ENV
		// IF NOT FOUND MARK WHOLE VAR AS -3
		i++;
	}
	if (expand_variable(lex, env)) // NEED TO CHECK PARSER CMDS & REDIRECTIONS SEPARATED
		return (1);
		// CHECK PARSE_COMMANDS, PARSE_REDIRECTIONS FOR VARIABLES
	if (parse_commands(lex, child))
		return (1);
	if (parser_redirection(lex, child))
		return (1);
	return (0);
}
