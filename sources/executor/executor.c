/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:23:42 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/22 15:23:43 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	executor(t_child **child, t_exec *exec, t_env *env)
{
	int	i;

	i = 0;
	if (get_heredoc(child, exec, env))
		return (1);
	while (child[i])
	{
		if (command_path(child[i], env))
			return (1);
		if (processes(child[i], exec, env))
			return (1);
		close_piping(child[i]);
		i++;
	}
	if (exec->need_exit == true)
	{
		free_struct(child, exec, NULL);
		free_env(env);
		exit(g_exit_code);
	}
	return (0);
}
