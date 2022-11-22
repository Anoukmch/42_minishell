/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:22:36 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/22 15:22:37 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	invalid_identifier(char *cmd)
{
	int	i;

	i = 1;
	if (cmd[0] == '\0' || (!ft_isalpha(cmd[0]) && cmd[0] != '_'))
	{
		g_exit_code = 1;
		return (perror_return_export_unset(cmd, "unset", 0));
	}
	while (cmd[i])
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
		{
			g_exit_code = 1;
			return (perror_return_export_unset(cmd, "unset", 0));
		}
		i++;
	}
	return (0);
}

char	**get_position_in_env(t_env *env, char *variable)
{
	int	i;

	i = 0;
	while (env->envp_bis[i])
	{
		if (ft_strncmp(env->envp_bis[i], variable,
				ft_strlen(variable)) == 0)
		{
			return (&env->envp_bis[i]);
		}
		i++;
	}
	return (NULL);
}

void	unset_variable(t_env *env, char *str)
{
	int		j;
	char	**tmp;

	j = 0;
	tmp = get_position_in_env(env, str);
	if (tmp)
	{
		free(tmp[j]);
		j++;
		while (tmp[j])
		{
			tmp[j - 1] = tmp[j];
			j++;
		}
		tmp[j - 1] = NULL;
	}
}

int	command_unset(t_child *child, t_env *env)
{
	int	i;

	i = 1;
	if (child->parser_cmd[i] == NULL)
		return (0);
	while (child->parser_cmd[i])
	{
		if (!invalid_identifier(child->parser_cmd[i]))
		{
			if (get_position_in_env(env, child->parser_cmd[i]))
				unset_variable(env, child->parser_cmd[i]);
		}
		i++;
	}
	return (0);
}
