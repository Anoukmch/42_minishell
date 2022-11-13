/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:05:29 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/11 14:44:39 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_env(t_exec *exec)
{
	if (exec->envp_bis == NULL)
	{
		exec->envp_bis = ft_calloc(3 + 1, sizeof(char *));
		if (exec->envp_bis == NULL)
			errorexit("ALLOC ERROR");
		exec->envp_bis[0] = ft_strjoin("PWD=", getcwd(NULL, 0));
		exec->envp_bis[1] = ft_strdup("SHLVL=1");
		exec->envp_bis[2] = ft_strdup("_=/usr/bin/env");
	}
}

void	executor(t_lex *lex, t_child **child, t_exec *exec)
{
	int	i;

	i = 0;
    if (command_path(lex, child, exec) != 0)
	{
		ft_putstr_fd("cmd path not found\n", 2);
		return ;
		// return (1);
	}
	// check_env(exec);
	while (child[i])
	{
		processes(child[i], exec);
		i++;
	}
	// int z = 0;
	// while(exec->envp_bis[z])
	// {
	// 	ft_printf("ENV: %s\n", exec->envp_bis[z]);
	// 	z++;
		
	// }
	// return (0);
}
