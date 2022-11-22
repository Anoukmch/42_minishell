/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:26:15 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/22 15:26:16 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_exec	*initialize_exec(t_lex *lex)
{
	t_exec	*exec;

	exec = ft_calloc(1, sizeof(t_exec));
	if (exec == NULL)
		return (NULL);
	exec->nbr_process = lex->no_processes;
	exec->end[0] = 0;
	exec->end[1] = 0;
	exec->buffer[0] = 0;
	exec->isheredoc = 0;
	exec->need_exit = false;
	return (exec);
}
