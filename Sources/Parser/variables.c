
#include "../../includes/minishell.h"

char	*is_variable_in_env(char *var, t_env *env)
{
	int	i;
	i = 0;
	while (env->envp_bis[i])
	{
		if (!ft_strncmp(var, env->envp_bis[i], ft_strlen(var)))
			return (env->envp_bis[i]);
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
		while (lex_string[env->c2] && (ft_isalnum(lex_string[env->c2]) || lex_string[env->c2] == '_'))
			env->c2++;
		var = ft_substr(lex_string, env->c1 + 1, (env->c2 - env->c1 - 1));
		if (!var || !var[0])
			return (0);
		all_env_var = is_variable_in_env(var, env);
		if (all_env_var)
			size = size + size_env_var(all_env_var, NULL);
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

char	*handle_var(char *lex_string, t_env *env)
{
	int	d;
	int	e;
	int sizearg;
	char	*var;
	char	*new_arg;
	char	*all_env_var;
	char	*env_var;
	int count;
	int k;
	int	i;

	i = 0;
	k = 0;
	d = 0;
	e = 0;
	sizearg = 0;
	count = nbr_dollar_sign(lex_string);
	sizearg = size_new_arg(lex_string, count, env);
	new_arg = ft_calloc((sizearg + 1), sizeof(char));
	if (!new_arg)
		return (NULL);
	env->c1 = 0;
	env->c3 = 0;
	while (k < count && sizearg != 0)
	{
		e = 0;
		while (lex_string[env->c1] && lex_string[env->c1] != -2)
			new_arg[env->c3++] = lex_string[env->c1++];
		if (!lex_string[env->c1])
			return (NULL);
		env->c2 = env->c1 + 1;
		while (lex_string[env->c2] && (ft_isalnum(lex_string[env->c2]) || lex_string[env->c2] == '_'))
			env->c2++;
		var = ft_substr(lex_string, env->c1 + 1, (env->c2 - env->c1 - 1));
		if (!var || !var[0])
			return (NULL);
		all_env_var = is_variable_in_env(var, env);
		if (all_env_var)
		{
			env_var = fill_env_var(all_env_var);
			if (!env_var)
				return (NULL);
			i = 0;
			while (env_var[i])
				new_arg[env->c3++] = env_var[i++];
			free(env_var);
		}
		free(var);
		env->c1 = env->c2;
		k++;
	}
	while (lex_string[env->c2] != '\0')
		new_arg[env->c3++] = lex_string[env->c2++];
	new_arg[env->c3] = '\0';
	free(lex_string);
	lex_string = ft_strdup(new_arg);
	free(new_arg);
	return (lex_string);
}

char	**rebuild_lex(t_lex *lex)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (lex->lexer[i])
	{
		if (!ft_strcmp(lex->lexer[i], "\0"))
			count++;
		i++;
	}
	lex->lexer_c = ft_calloc((i + 1 - count), sizeof(char *));
	if (!lex->lexer_c)
		return (NULL);
	i = 0;
	while (lex->lexer[i])
	{
		if (ft_strcmp(lex->lexer[i], "\0"))
		{
			lex->lexer_c[j] = ft_strdup(lex->lexer[i]);
			if (!lex->lexer_c[j])
				return (NULL);
			j++;
		}
		i++;
	}
	lex->lexer_c[j] = NULL;
	free_array(lex->lexer);
	lex->lexer = lex->lexer_c; /* can I do that or do I need to remalloc ? */
	return (lex->lexer);
}

int	expand_variable(t_lex *lex, t_env *env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (lex->lexer[i])
	{
		if (lex->lexer[i][0] == -2 && lex->lexer[i][1] == '?' && !lex->lexer[i][2])
		{
			tmp = ft_itoa(g_exit_code);
			if (!tmp)
				return (1);
			free(lex->lexer[i]);
			lex->lexer[i] = ft_strdup(tmp);
			if (!lex->lexer[i])
				return (1);
			free(tmp);
		}
		else if (ft_strchr(lex->lexer[i], -2) != NULL)
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

