/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:23:18 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/22 15:23:19 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	switch_put(t_child *child, t_exec *exec)
{
	if (child->parser_redirect_input[0] != NULL)
	{
		if (dup2(child->fd_in, STDIN_FILENO) < 0)
			perror_exit_status(NULL, "Error file_in", 1);
	}
	else if (child->parser_redirect_input[0] == NULL && child->id != 0)
	{
		if (dup2(exec->buffer[0], STDIN_FILENO) < 0)
			perror_exit_status(NULL, "Error piping", 1);
	}
	if (child->parser_redirect_output[0] != NULL)
	{
		if (dup2(child->fd_out, STDOUT_FILENO) < 0)
			perror_exit_status(NULL, "Error file_out", 1);
	}
	else if (child->parser_redirect_output[0] == NULL
		&& child->id != (exec->nbr_process - 1))
	{
		if (dup2(exec->end[1], STDOUT_FILENO) < 0)
			perror_exit_status(NULL, "Error piping", 1);
	}
	return (0);
}

int	close_pipe(t_exec *exec, t_child *child)
{
	if (exec->nbr_process > 1)
	{
		close(exec->end[0]);
		close(exec->end[1]);
		if (child->id != 0 && child->id != (exec->nbr_process - 1))
			close(exec->buffer[0]);
	}
	if (child->parser_redirect_input[0])
		close(child->fd_in);
	if (child->parser_redirect_output[0])
		close(child->fd_out);
	if (exec->isheredoc == 1)
		unlink(child->file_buff);
	return (0);
}

void	close_piping(t_child *child)
{
	if (child->parser_redirect_input[0])
		close(child->fd_in);
	if (child->parser_redirect_output[0])
		close(child->fd_out);
}
