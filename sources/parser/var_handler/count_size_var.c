/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_size_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:24:49 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/22 15:24:50 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*count_var(char *lex_string, t_env *env, int *size)
{
	char	*var;

	while (lex_string[env->c1] && lex_string[env->c1] != -2)
	{
		(*size)++;
		env->c1++;
	}
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
		while (lex_string[env->c2] && (ft_isalnum(lex_string[env->c2])
				|| lex_string[env->c2] == '_'))
			env->c2++;
		var = ft_substr(lex_string, env->c1 + 1, (env->c2 - env->c1 - 1));
	}
	return (var);
}

int	count_new_arg_env_var(char *var, t_env *env, int *size)
{
	char	*tmp;
	char	*all_env_var;

	if (var[0] != '?')
	{
		all_env_var = is_variable_in_env(var, env);
		if (all_env_var)
			*size = *size + size_env_var(all_env_var, NULL);
	}
	else
	{
		tmp = ft_itoa(g_exit_code);
		if (!tmp)
			return (1);
		*size = *size + ft_strlen(tmp);
	}
	return (0);
}

int	count_new_arg(char *lex_string, t_env *env, int size)
{
	char	*var;

	var = count_var(lex_string, env, &size);
	if (!var)
		return (-1);
	if (count_new_arg_env_var(var, env, &size))
		return (-1);
	free(var);
	env->c1 = env->c2;
	return (size);
}

int	size_new_arg(char *lex_string, int count, t_env *env)
{
	int	k;
	int	size;

	env->c1 = 0;
	size = 0;
	k = 0;
	while (k < count)
	{
		size = count_new_arg(lex_string, env, size);
		if (size == -1)
			return (-1);
		k++;
	}
	while (lex_string[env->c2] != '\0')
	{
		size++;
		env->c2++;
	}
	return (size);
}
