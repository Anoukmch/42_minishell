/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:05:29 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/09 12:02:08 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	executor(t_lex *lex, t_child **child, t_exec *exec)
{
	int	i;

	i = 0;
    command_path(lex, child, exec);
	while (child[i])
	{
		processes(child[i], exec);
		i++;
	}
}
