/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_size_var_hd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:25:17 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/22 15:25:18 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*count_var_hd(char *lex_string, t_env *env, int *size)
{
	char	*var;

	while (lex_string[env->c1] && lex_string[env->c1] != '$')
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

int	count_new_arg_hd(char *lex_string, t_env *env, int size)
{
	char	*var;

	var = count_var_hd(lex_string, env, &size);
	if (!var)
		return (-1);
	if (!var[0])
		return (0);
	if (count_new_arg_env_var(var, env, &size))
		return (-1);
	free(var);
	env->c1 = env->c2;
	return (size);
}

int	size_new_arg_hd(char *lex_string, int count, t_env *env)
{
	int	k;
	int	size;

	env->c1 = 0;
	size = 0;
	k = 0;
	while (k < count)
	{
		size = count_new_arg_hd(lex_string, env, size);
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
