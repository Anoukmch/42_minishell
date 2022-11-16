
#include "../../includes/minishell.h"

char	*is_variable_in_env(char *var, t_env	*env)
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
		all_env_var = is_variable_in_env(var, env);
		size = size + size_env_var(all_env_var, NULL);
		free(var);
		env->c1 = env->c2;
		k++;
	}
	return (size + j);
	return (-1);
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
		if (sizearg == -1)
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
			env_var = fill_env_var(all_env_var);
			if (!env_var)
				return (NULL);
			printf("env_var : %s\n", env_var);
			i = 0;
			while (env_var[i])
				new_arg[env->c3++] = env_var[i++];
			printf("new : %s\n", new_arg);
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
	int	i;

	i = 0;
	while (lex->lexer[i])
	{
		/* Remplacer les -2 "alone" par des $ */
		if (ft_strchr(lex->lexer[i], -2) != NULL)
			lex->lexer[i] = handle_var(lex->lexer[i], env);
		i++;
	}
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
	// DELETE QUOTES EXCEPT HERE_DOC
	// MARKING VARIABLES THAT SHOULD GET EXPAND AS -2
	while (child[k])
	{
		while (lex->lexer[i] && lex->lexer)
		{
			if (!ft_strcmp(lex->lexer[i], "<<"))
			{
				i++;
				z = 0;
				while (lex->lexer[i][z])
				{
					if (lex->lexer[i][z] == 39 || lex->lexer[i][z] == '"')
					{
						child[k]->heredoc_quotes = 1;
						break ;
					}
					z++;
				}
			}
			else if (!strcmp(lex->lexer[i], "<") || !strcmp(lex->lexer[i], ">") || !strcmp(lex->lexer[i], ">>") || !strcmp(lex->lexer[i], "<<"))
				i++;
			else
			{
				// HERE_DOC EOF $ IS NOT ALLOWED TO BE MARKED (should work now)
				if (i == 0)
				{
					if (mark_quotes(lex->lexer[i], NULL) != 0)
						return (1);
				}
				else if (mark_quotes(lex->lexer[i], lex->lexer[i - 1]) != 0)
					return (1); //RETURN(1);
				lex->lexer[i] = delete_quotes(lex->lexer[i]);
				if (!lex->lexer[i])
					return (1);
			}
			i++;
		}
		k++;
	}
	expand_variable(lex, env);
	if (parse_commands(lex, child))
		return (1);
	if (parser_redirection(lex, child))
		return (1);
	return (0);
}
