/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:23:48 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/22 15:24:03 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_current_directorypath(t_child *child)
{
	char	*tmp;
	char	*dir;

	tmp = NULL;
	dir = getcwd(NULL, 0);
	if (!ft_strcmp(dir, "/"))
		tmp = ft_strdup(child->parser_cmd[0]);
	else if (ft_strchr(child->parser_cmd[0], '/'))
		tmp = ft_strdup(dir);
	else
		tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (1);
	free (dir);
	child->command = ft_strjoin(tmp, child->parser_cmd[0]);
	if (!child->command)
		return (1);
	free (tmp);
	if (access(child->command, 0) == 0)
		return (0);
	free (child->command);
	child->command = NULL;
	return (0);
}

static int	check_existing_path(t_env *env, t_child *child)
{
	if (env->envp_bis == NULL || env->envp_path == NULL
		|| ft_strchr(child->parser_cmd[0], '/') != NULL)
	{
		child->command = ft_strdup(child->parser_cmd[0]);
		if (!child->command)
			return (1);
		if (access(child->command, 0) == 0)
			return (0);
		else
			child->command = NULL;
	}
	return (0);
}

static int	find_command_path(t_env *env, t_child *child)
{
	int	i;

	i = 0;
	while (env->envp_bis && env->envp_path[i])
	{
		child->command = ft_strjoin(env->envp_path[i], child->parser_cmd[0]);
		if (!child->command)
			return (1);
		if (access(child->command, 0) == 0)
			return (0);
		free(child->command);
		i++;
	}
	child->command = NULL;
	return (0);
}

static int	check_path(t_child *child, t_env *env)
{
	if (check_current_directorypath(child))
		return (1);
	if (!child->command && ft_strchr(child->parser_cmd[0], '/'))
	{
		if (check_existing_path(env, child))
			return (1);
		if (!child->command)
			return (0);
		return (0);
	}
	if (get_path_from_env(env, child))
	{
		free_array(env->envp_path);
		return (1);
	}
	if (find_command_path(env, child))
	{
		free_array(env->envp_path);
		return (1);
	}
	free_array(env->envp_path);
	if (child->command)
		return (0);
	return (0);
}

int	command_path(t_child *child, t_env *env)
{
	if (child->parser_cmd[0])
	{
		if (!ft_strcmp(child->parser_cmd[0], "")
			|| !ft_strcmp(child->parser_cmd[0], ".."))
			return (0);
		if (check_builtins_env(child)
			|| check_builtins_other(child))
			return (1);
		if (child->command)
			child->isbuiltin = true;
		if (child->command == NULL)
		{
			if (check_path(child, env))
				return (0);
		}
	}
	return (0);
}
