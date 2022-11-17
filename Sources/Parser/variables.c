
#include "../../includes/minishell.h"

char	*is_variable_in_env(char *var, t_env *env)
{
	int	i;

	i = 0;
	printf("VAR IN ENV: %s\n", var);
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
	return (1); /* no = means an error */
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
	env_var = ft_calloc(size + 1, sizeof(char));
	if (!env_var)
		return (NULL);
	while (all_env_var[j])
		env_var[i++] = all_env_var[j++];
	env_var[i] = '\0';
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

	size = 0;
	k = 0;
	j = 0;
	while (k < count)
	{
		if (k == 0)
		{
			while (lex_string[j])
			{
				if (lex_string[j] == -2)
					break ;
				j++;
			}
		}
		e = 0;
		while (lex_string[env->c1] && lex_string[env->c1] != -2)
			env->c1++;
		if (!lex_string[env->c1])
			return (0);
		env->c2 = env->c1 + 1;
		printf("env C2: %d\n", env->c2);
		while (lex_string[env->c2] && (lex_string[env->c2] == '_'
			|| ft_isalnum(lex_string[env->c2]))) //GET END OF VAR
			env->c2++;
		printf("env C2: %d\n", env->c2);
		printf("env C1: %d\n", env->c1);
		var = ft_substr(lex_string, env->c1 + 1, env->c2 - (env->c1 + 1)); //HERE
		if (!var)
			return (0);
		printf("VAR: %s\n", var);
		env->c2 = env->c1 + 1;
		while (lex_string[env->c2] && (lex_string[env->c2] == '_'
			|| ft_isalnum(lex_string[env->c2])))
			var[e++] = lex_string[env->c2++];
		var[e] = '\0';
		printf("WEIRD VAR: %s\n", var);
		all_env_var = is_variable_in_env(var, env);
		printf("VAR IN ENV?: %s\n", all_env_var);
		if (all_env_var)
			size = size + size_env_var(all_env_var, NULL);
		free(var);
		env->c1 = env->c2;
		k++;
	}
	printf("size : %d\n", size + j);
	return (size + j);
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
	char	*all_env_var; /* do I need to calloc all_env_var ? */
	char	*env_var;
	int count;
	int jsp;
	int	i;

	i = 0;
	jsp = 0;
	env->c1 = 0;
	env->c2 = env->c1 + 1;
	d = 0;
	env->c3 = 0;
	e = 0;
	sizearg = 0;
	count = nbr_dollar_sign(lex_string);
	if (!lex_string || !env)
		printf("Fail");
	else
	{
		sizearg = size_new_arg(lex_string, count, env);
		if (sizearg == 0)
			return (NULL);
		new_arg = ft_calloc((sizearg + 1), sizeof(char));
		if (!new_arg)
			return (NULL);
		env->c1 = 0;
		env->c2 = env->c1 + 1;
		while (jsp < count)
		{
			if (jsp == 0)
			{
				while (lex_string[d] != -2)
					new_arg[env->c3++] = lex_string[d++];
			}
			e = 0;
			env->c2 = env->c1 + 1;
			while (lex_string[env->c1] && lex_string[env->c1] != -2)
				env->c1++;
			if (!lex_string[env->c1])
				return (0);
			while (lex_string[env->c2] && lex_string[env->c2] != -2)
				env->c2++;
			var = ft_substr(lex_string, env->c1 + 1, (env->c2 - env->c1));
			if (!var)
				return (0);
			env->c2 = env->c1 + 1;
			while (lex_string[env->c2] && lex_string[env->c2] != -2)
				var[e++] = lex_string[env->c2++];
			var[e] = '\0';
			printf("var : %s\n", var);
			all_env_var = is_variable_in_env(var, env);
			printf("all_env_var : %s\n", all_env_var);
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
			jsp++;
		}
		new_arg[env->c3] = '\0';
		free(lex_string);
		lex_string = ft_strdup(new_arg);
		free(new_arg);
	}
	return (lex_string);
}

int	expand_variable(t_lex *lex, t_env *env)
{
	int		i;
	int		j;
	int		size;
	char	*tmp;

	size = 0;
	i = 0;
	j = 0;
	while (lex->lexer[i])
	{
		// size = ft_strlen(lex->lexer[i]); //size protecten if size = 0
		// if (lex->lexer[i][size - 1] == -2)
		// 	lex->lexer[i][size - 1] = '$';
		if (lex->lexer[i][0] == -2 && lex->lexer[i][1] == '?' && !lex->lexer[i][2])
		{
			printf("exit code : %d\n", g_exit_code);
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
			lex->lexer[i] = handle_var(lex->lexer[i], env);
		i++;
	}
	return (0);
}