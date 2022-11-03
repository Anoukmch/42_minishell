/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 13:53:57 by amechain          #+#    #+#             */
/*   Updated: 2022/11/03 13:55:59 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	switch_put(t_child *child, t_exec *exec)
{
	if (child->parser_redirect_input[0] != NULL)
	{
		if (dup2(child->fd_in, STDIN_FILENO) < 0)
			error ("Dup2 infile failed");
	}
	else if (child->parser_redirect_input[0] == NULL && child->id != 0)
	{
		if (dup2(exec->buffer[0], STDIN_FILENO) < 0)
			error ("Dup2 infile failed");
	}
	if (child->parser_redirect_output[0] != NULL)
	{
		if (dup2(child->fd_out, STDOUT_FILENO) < 0)
			error ("Dup2 outfile failed");
	}
	else if (child->parser_redirect_output[0] == NULL && child->id != (exec->nbr_process - 1))
	{
		if (dup2(exec->end[1], STDOUT_FILENO) < 0)
			error ("Dup2 outfile failed");
	}
}

void	close_pipe(t_exec *exec, t_child *child)
{
	if (exec->nbr_process > 1)
	{
		close(exec->end[0]);
		close(exec->end[1]);
		if (child->id != 0 && child->id != (exec->nbr_process - 1))
			close(exec->buffer[0]);
	}
	if (child->parser_redirect_input[0] != NULL)
		close(child->fd_in);
	if (child->parser_redirect_output[0] != NULL)
		close(child->fd_out);
}

void	processes(t_child *child, t_exec *exec)
{
	pid_t	child;
	int		i;

	i = 0;
	if (exec->nbr_process > 1 && child->id != (exec->nbr_process - 1))
	{
		if (pipe(exec->end) < 0)
			error ("Pipe fail", NULL);
	}
	child = fork();
	if (child < 0)
		error("Fork fail", NULL);
	else if (child == 0)
	{
		if (child->parser_redirect_input[0] != NULL)
			get_infile(child);
		if (child->parser_redirect_output[0] != NULL)
			get_outfile(child);
		switch_put(child, exec);
		close_pipe(exec, child);
		exec->buffer[0] = exec->end[0];
	}
}
