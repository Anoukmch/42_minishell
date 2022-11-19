
#include "../../includes/minishell.h"

char	*is_variable_in_env(char *var, t_env *env)
{
	int	i;

	i = 0;
	while (env->envp_bis[i])
	{
		if (!ft_strncmp(var, env->envp_bis[i], ft_strlen(var)))
		{
			if (env->envp_bis[i][ft_strlen(var)] == '='
				|| env->envp_bis[i][ft_strlen(var)] == '\0')
				return (env->envp_bis[i]);
		}
		i++;
	}
	return (NULL);
}

int	size_env_var(char *all_env_var, int *j)
{
	int	i;
	int size;

	i = 0;
	size = 0;
	while(all_env_var[i])
	{
		if (all_env_var[i] == '=')
		{
			if (j)
				*j = i + 1;
			size = ft_strlen(all_env_var) - i - 1;
			return (size);
		}
		i++;
	}
	if (j)
		*j = i;
	return (0);
}

char	*fill_env_var(char *all_env_var)
{
	int		i;
	int		j;
	int		size;
	char	*env_var;

	i = 0;
	j = 0;
	size = size_env_var(all_env_var, &j);
	env_var = ft_substr(all_env_var, j, size);
	if (!env_var)
		return (NULL);
	return (env_var);
}

bool	is_there_sign_before(char *lex_string, int j)
{
	j = j - 1;
	while (j >= 0)
	{
		if (lex_string[j] == -2)
			return (true);
		j--;
	}
	return (false);
}

int	size_new_arg(char *lex_string, int count, t_env *env)
{
	int	j;
	int	k;
	int size;
	int e;
	char *all_env_var;
	char	*var;
	char	*tmp;

	env->c1 = 0;
	size = 0;
	k = 0;
	j = 0;
	while (k < count)
	{
		e = 0;
		while (lex_string[env->c1] && lex_string[env->c1] != -2)
		{
			size++;
			env->c1++;
		}
		if (!lex_string[env->c1])
			return (0);
		env->c2 = env->c1 + 1;
		if (lex_string[env->c2] == '?')
		{
			var = ft_substr(lex_string, env->c1 + 1, 1);
			env->c2++;
		}
		else
		{
			while (lex_string[env->c2] && (ft_isalnum(lex_string[env->c2]) || lex_string[env->c2] == '_'))
				env->c2++;
			var = ft_substr(lex_string, env->c1 + 1, (env->c2 - env->c1 - 1));
		}
		if (!var || !var[0])
			return (0);
		if (var[0] != '?')
		{
			all_env_var = is_variable_in_env(var, env);
			if (all_env_var)
				size = size + size_env_var(all_env_var, NULL);
		}
		else
		{
			tmp = ft_itoa(g_exit_code);
			if (!tmp)
				return (0);
			size = size + ft_strlen(tmp);
		}
		free(var);
		env->c1 = env->c2;
		k++;
	}
	while (lex_string[env->c2] != '\0')
	{
		size++;
		env->c2++;
	}
	return (size);
}

int	nbr_dollar_sign(char *lex_string)
{
	int	size;
	int count;
	count = 0;
	size = ft_strlen(lex_string) - 1;
	while (size >= 0)
	{
		if (lex_string[size] == -2)
			count++;
		size--;
	}
	return (count);
}

char	*get_var(char *lex_string, t_env *env)
{
	char	*var;

	while (lex_string[env->c1] && lex_string[env->c1] != -2)
		env->new_arg[env->c3++] = lex_string[env->c1++];
	if (!lex_string[env->c1])
		return (NULL);
	env->c2 = env->c1 + 1;
	if (lex_string[env->c2] == '?')
	{
		var = ft_substr(lex_string, env->c1 + 1, 1);
		env->c2++;
	}
	else
	{
		while (lex_string[env->c2] && (ft_isalnum(lex_string[env->c2]) || lex_string[env->c2] == '_'))
			env->c2++;
		var = ft_substr(lex_string, env->c1 + 1, (env->c2 - env->c1 - 1));
	}
	return (var);
}

int	fill_new_arg_env_var(char *var, t_env *env)
{
	int		i;
	char	*env_var;
	char	*all_env_var;

	i = 0;
	env_var = NULL;
	if (var[0] != '?')
	{
		all_env_var = is_variable_in_env(var, env);
		if (all_env_var)
		{
			env_var = fill_env_var(all_env_var);
			if (!env_var)
				return (1);
		}
	}
	else
	{
		env_var = ft_itoa(g_exit_code);
		if (!env_var)
			return (1);
	}
	while (env_var && env_var[i])
		env->new_arg[env->c3++] = env_var[i++];
	if (env_var)
		free(env_var);
	return (0);
}

int	fill_new_arg(char *lex_string, t_env *env)
{
	char	*var;

	var = get_var(lex_string, env);
	if (!var || !var[0])
		return (1);
	if (fill_new_arg_env_var(var, env))
		return (1);
	free(var);
	env->c1 = env->c2;
	return (0);
}

char	*handle_var(char *lex_string, t_env *env)
{
	int 	k;
	int	count;
	int	sizearg;

	k = 0;
	count = nbr_dollar_sign(lex_string);
	sizearg = size_new_arg(lex_string, count, env);
	env->new_arg = NULL;
	env->new_arg = ft_calloc((sizearg + 1), sizeof(char));
	if (!env->new_arg)
		return (NULL);
	env->c1 = 0;
	env->c3 = 0;
	while (k < count && sizearg != 0)
	{
		if (fill_new_arg(lex_string, env))
			return (NULL);
		k++;
	}
	while (lex_string[env->c2] != '\0' && sizearg != 0)
		env->new_arg[env->c3++] = lex_string[env->c2++];
	env->new_arg[env->c3] = '\0';
	free(lex_string);
	lex_string = ft_strdup(env->new_arg);
	free(env->new_arg);
	return (lex_string);
}

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

void fill_new_lex(t_lex *lex)
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
	int count;

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

int	expand_variable(t_lex *lex, t_env *env)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (lex->lexer[i])
	{
		if (ft_strchr(lex->lexer[i], -2) != NULL)
		{
			lex->lexer[i] = handle_var(lex->lexer[i], env);
			if (!lex->lexer[i])
				return (1);
		}
		i++;
	}
	lex->lexer = rebuild_lex(lex);
	return (0);
}

