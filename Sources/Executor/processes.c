/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 13:53:57 by amechain          #+#    #+#             */
/*   Updated: 2022/10/31 12:50:56 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	switch_put(t_child *child, int *end)
{
	if (child->parser_redirect_input[0] != NULL)
	{
		if (dup2(child->fd_in, STDIN_FILENO) < 0)
			error ("Dup2 infile failed");
	}
	else if (child->parser_redirect_input[0] == NULL && child->id != 0)
	{
		if (dup2(end[0], STDIN_FILENO) < 0)
			error ("Dup2 infile failed");
	}
	if (child->parser_redirect_output[0] != NULL)
	{
		if (dup2(child->fd_out, STDOUT_FILENO) < 0)
			error ("Dup2 outfile failed");
	}
	else if (child->parser_redirect_output[0] == NULL && child->id != /* Last process */)
	{
		if (dup2(end[1], STDOUT_FILENO) < 0)
			error ("Dup2 outfile failed");
	}
	/* Close pipe */
}

void	processes(t_child *child)
{
	int		end[2];
	pid_t	child;
	int		i;

	i = 0;
	/* Conditional if we have the pipe symbol */
	if (pipe(end) < 0)
		error ("Pipe fail", NULL);
	child = fork();
	if (child < 0)
		error("Fork fail", NULL);
	else if (child == 0)
	{
		if (child->parser_redirect_input[0] != NULL)
			get_infile(child);
		if (child->parser_redirect_output[0] != NULL)
			get_outfile(child);
		switch_put(child, end);
	}
	/* !!! Close fd !!! */
}
