/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:23:22 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/22 15:23:23 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	processes(t_child *child, t_exec *exec, t_env *env)
{
	if (exec->nbr_process == 1 && child->isbuiltin == true)
	{
		if (single_builtin(child, exec, env))
		{
			g_exit_code = 1;
			return (1);
		}
		else if (ft_strcmp(child->command, "unset")
			&& ft_strcmp(child->command, "export")
			&& ft_strcmp(child->command, "exit"))
			g_exit_code = 0;
	}
	else
	{
		if (child_exec(child, exec, env))
			return (1);
	}
	return (0);
}
