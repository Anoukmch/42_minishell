/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:05:29 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/07 17:27:09 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	executor(t_lex *lex, t_child **child, t_exec *exec)
{
        //command_path(lex, child, exec);
		//command_export (child[0]->parser_cmd);
		if (!ft_strcmp(child[0]->parser_cmd[0], "pwd"))
			command_pwd();
		if (!ft_strcmp(child[0]->parser_cmd[0], "echo"))
			command_echo(child[0]);
		if (!ft_strcmp(child[0]->parser_cmd[0], "cd"))
			command_cd(child[0]);
		if (!ft_strcmp(child[0]->parser_cmd[0], "exit"))
			command_exit(child[0]);
		//command_exit(child[0]);
		exec = (void*)exec;
		lex = (void*)lex;
		child = (void*)child;
}
