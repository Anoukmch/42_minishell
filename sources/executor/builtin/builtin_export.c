/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:22:22 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/22 15:22:23 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	invalid_identifier(char *cmd)
{
	int	i;

	i = 0;
	if ((!ft_isalpha(cmd[0]) && cmd[0] != '_'))
	{
		g_exit_code = 1;
		return (perror_return_export_unset(cmd, "export", 0));
	}
	while (cmd[i] && cmd[i] != '=')
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
		{
			g_exit_code = 1;
			return (perror_return_export_unset(cmd, "export", 0));
		}
		i++;
	}
	return (0);
}

int	export_variable(char *str, t_env *env)
{
	char	*variablename;
	int		replace;

	variablename = NULL;
	variablename = str;
	replace = replace_variable(env, variablename, NULL);
	if (replace == 1)
		return (1);
	if (!replace)
	{
		env->envp_bis = create_new_env(env, variablename, NULL);
		if (!env->envp_bis)
			return (1);
	}
	return (0);
}

int	env_variable(char *str, t_env *env)
{
	char	*variablename;
	char	*content;
	int		replace;

	variablename = ft_substr(str, 0,
			ft_strlen(str) - ft_strlen(ft_strchr(str, '=')));
	content = ft_substr(str, ft_strlen(variablename) + 1,
			ft_strlen(ft_strchr(str, '=')) + 1);
	if (ft_strlen(content) == 0)
		content = ft_strdup("");
	if (!content || !variablename)
		return (1);
	replace = replace_variable(env, variablename, content);
	if (replace == 1)
		return (1);
	if (!replace)
	{
		env->envp_bis = create_new_env(env, variablename, content);
		if (!env->envp_bis)
			return (1);
	}
	free (variablename);
	free (content);
	return (0);
}

int	command_export(t_child *child, t_env *env)
{
	int	i;

	i = 1;
	if (child->parser_cmd[i] == NULL)
	{
		if (no_options(env))
			return (1);
		return (0);
	}
	while (child->parser_cmd[i])
	{
		if (!invalid_identifier(child->parser_cmd[i]))
		{
			if (ft_strchr(child->parser_cmd[i], '=')
				&& env_variable(child->parser_cmd[i], env))
				return (1);
			else if (!ft_strchr(child->parser_cmd[i], '=')
				&& export_variable(child->parser_cmd[i], env))
				return (1);
		}
		i++;
	}
	return (0);
}
