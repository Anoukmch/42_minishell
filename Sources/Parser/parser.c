
#include "../../includes/minishell.h"

int	mark_variables(char *str)
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
		else if ((quote == '\"' || quote == '\0') && str[i] == '$')
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

int	quotes_after_dollarsign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == -2 && (str[i + 1] == '\'' || str[i + 1] == '\"'))
			str[i] = -3;
		i++;
	}
	return (0);
}

char	*variable_in_env(char *var, t_env *env)
{
	int	i;

	i = 0;
	printf("VAR IN ENV: %s\n", var);
	while (env->envp_bis[i])
	{
		if (!ft_strncmp(var, env->envp_bis[i], ft_strlen(var)))
		{
			if (!ft_strchr(env->envp_bis[i], '='))
				return (NULL);
			return (env->envp_bis[i]);
		}
		i++;
	}
	return (NULL);
}

int	not_in_env (char *str, char *var)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == -2)
		{
			ft_memset(&str[i], -3, ft_strlen(var) + 1);
			return (0);
		}
	}
	return (0);
}

char	*replace_var_with_content(char *str, char *var, char *env_var)
{
	char *pos_in_str;
	char *new_lexline;
	int	size;
	int	count_size;

	pos_in_str = NULL;
	pos_in_str = ft_strchr(str, -2);
	size = ft_strlen(var) + 1;
	count_size = ft_strlen(ft_strchr(env_var, '=')) - 1;
	new_lexline  = ft_calloc(ft_strlen(str) - size + count_size, sizeof(char));
	if (!new_lexline)
		return (NULL);
	new_lexline = ft_memcpy(new_lexline, str, pos_in_str - str);
	new_lexline = ft_memcpy(new_lexline + (pos_in_str - str), ft_strchr(env_var, '=') + 1, count_size);
	new_lexline = ft_memcpy(new_lexline + (pos_in_str - str) + count_size, pos_in_str + size, (pos_in_str - str) + size);
	return (new_lexline);
}

int check_if_var_in_env(t_lex *lex, int i, char *var, t_env *env)
{
	char *env_var;

	env_var = variable_in_env(var, env);
	if (env_var)
	{
		lex->lexer[i] = replace_var_with_content(lex->lexer[i], var, env_var);
		printf("REPLACE\n");
	}
	else
	{
		if (not_in_env(lex->lexer[i], var))
			return (1);
		printf("MARK AS -3");
	}
	return (0);
}

int get_variable_name(t_lex *lex, int i, t_env *env)
{
	int	j;
	int	start;
	int end;
	char *var;

	j = 0;
	start = -1;
	end = -1;
	var = NULL;
	while(lex->lexer[i][j])
	{
		if (lex->lexer[i][j] == -2)
			start = j;
		else if (i > start && !ft_isalnum(lex->lexer[i][j]) && lex->lexer[i][j] != '_')
		{
			end = j;
			break ;
		}
		j++;
	}
	if (start != -1 && end == -1)
		end = j;
	if (end != -1)
	{
		var = ft_substr(lex->lexer[i], start + 1, end - 1);
		if (!var)
			return (1);
		if (check_if_var_in_env(lex, i, var, env))
			return (1);
		// CHECK VAR IN ENV
	}
	printf("VAR: %s\n", var);
	return (0);
}

// while (lex_string[env->c2] && (lex_string[env->c2] == '_'
// 			|| ft_isalnum(lex_string[env->c2]))) //GET END OF VAR

int	parser(t_lex *lex, t_child	**child, t_env	*env)
{
	int	i;
	int	k;
	int	z;

	i = 0;
	k = 0;
	z = 0;
	// MARK VARIABLES AS -2
	while (lex->lexer[i])
	{
		if (mark_variables(lex->lexer[i]))
			return (1);
		if (check_dollarsign(lex->lexer[i]))
			return (1);
		if (quotes_after_dollarsign(lex->lexer[i]))
			return (1);
		if (get_variable_name(lex, i, env))
			return (1);
		// EXPAND VARIABLES IF FOUND IN ENV
		// IF NOT FOUND MARK WHOLE VAR AS -3
		// printf("str after function: %s\n", lex->lexer[i]);
		i++;
	}
	// print_lexer(lex);
	// if (expand_variable(lex, env)) // NEED TO CHECK PARSER CMDS & REDIRECTIONS SEPARATED
	// 	return (1);
	if (env)
		printf("test");
		// CHECK PARSE_COMMANDS, PARSE_REDIRECTIONS FOR VARIABLES
	if (parse_commands(lex, child))
		return (1);
	if (parser_redirection(lex, child))
		return (1);
	return (0);
}
