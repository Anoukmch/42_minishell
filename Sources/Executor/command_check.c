/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:01:51 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/07 15:49:40 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	check_path(t_lex *lex, t_child **child, t_exec *exec)
{
	int	i;

	i = 0;
	if (exec->envp_bis == NULL || exec->envp_path == NULL
		|| ft_strchr(child[lex->iter]->parser_cmd[0], '/') != NULL)
	{
		child[lex->iter]->command = child[lex->iter]->parser_cmd[0];
		if (access(child[lex->iter]->command, 0) == 0)
			return ;
		else
		{
			free (child[lex->iter]->command);
			return ;
		}
	}
	while (exec->envp_bis && exec->envp_path[i])
	{
		child[lex->iter]->command = ft_strjoin(exec->envp_path[i],
				child[lex->iter]->parser_cmd[0]);
		if (access(child[lex->iter]->command, 0) == 0)
			return ;
		free(child[lex->iter]->command);
		i++;
	}
	child[lex->iter]->command = NULL;
}

static void	check_builtins(t_lex *lex, t_child **child)
{
	if (ft_strncmp("echo", child[lex->iter]->parser_cmd[0], 5) == 0)
		child[lex->iter]->command = ft_substr("echo", 0, 5);
	else if (ft_strncmp("cd", child[lex->iter]->parser_cmd[0], 3) == 0)
		child[lex->iter]->command = ft_substr("cd", 0, 3);
	else if (ft_strncmp("pwd", child[lex->iter]->parser_cmd[0], 4) == 0)
		child[lex->iter]->command = ft_substr("pwd", 0, 4);
	else if (ft_strncmp("export", child[lex->iter]->parser_cmd[0], 7) == 0)
		child[lex->iter]->command = ft_substr("export", 0, 7);
	else if (ft_strncmp("unset", child[lex->iter]->parser_cmd[0], 6) == 0)
		child[lex->iter]->command = ft_substr("unset", 0, 6);
	else if (ft_strncmp("env", child[lex->iter]->parser_cmd[0], 4) == 0)
		child[lex->iter]->command = ft_substr("env", 0, 4);
	else if (ft_strncmp("exit", child[lex->iter]->parser_cmd[0], 5) == 0)
		child[lex->iter]->command = ft_substr("exit", 0, 5);
}
static void	check_commands(t_lex *lex, t_child **child, t_exec *exec)
{
	check_builtins(lex, child);
	if (child[lex->iter]->command == NULL)
		check_path(lex, child, exec);
}

void	command_path(t_lex *lex, t_child **child, t_exec *exec)
{
	lex->iter = 0;
	while (child[lex->iter])
	{
		check_commands (lex, child, exec);
		if (child[lex->iter]->command == NULL)
			errorexit ("invalid command!");
		lex->iter++;
	}
	// PRINT COMMAND PATHS
	int k = 0;
	while (child[k])
	{
		printf ("commandpath for child %d: %s\n", k, child[k]->command);
		k++;
	}
}
