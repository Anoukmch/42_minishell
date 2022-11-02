/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:44:13 by amechain          #+#    #+#             */
/*   Updated: 2022/11/02 15:48:34 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_exec *initialize_exec(t_lex *lex, char **envp)
{
	t_exec *exec;

    exec = ft_calloc(1, sizeof(t_exec));
     if (exec == NULL)
        errorexit("check initializiation of structs");
    exec->nbr_process = lex->no_processes;
    exec->envp_bis = envp;
    exec->envp_line = getenv("PATH");
    exec->envp_path = ft_split(exec->envp_line, ':');
	if (!exec->envp_path)
		 errorexit("check initializiation of structs");
	return(exec);
}
