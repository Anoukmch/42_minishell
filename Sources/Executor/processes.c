/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 13:53:57 by amechain          #+#    #+#             */
/*   Updated: 2022/10/25 17:24:48 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_infile()
{
	int	fd_in;

	if (parser_redirect[0] && parser_redirect[1] == NULL)
	{
		fd_in = open(parser_redirect[0], O_RDONLY);
		if (fd_in < 0)
			error ("Open failed", NULL);
	}
	else if (parser_redirect[0] && parser_redirect[1])
	{
		fd_in = open(parser_redirect[0], O_RDONLY);
		if (fd_in < 0)
			error ("Open failed", NULL);
	}
	else if (parser_redirect[0] == NULL && parser_redirect[1])
	{
		here_doc();
		fd_in = open(parser_redirect[0], O_RDONLY);
		if (fd_in < 0)
			error ("Open failed", NULL);
	}
	else
		return (STDIN_FILENO);
	return (fd_in);
}

int	get_outfile()
{
	int	fd_out;

	return (fd_out);
}



void	processes()
{
	int		end[2];
	pid_t	child;

	/* Conditional if we have the pipe symbol */
	if (pipe(end) < 0)
		error ("Pipex fail", NULL);
	child = fork();
	if (child < 0)
		error("Fork fail", NULL);
	else if (child == 0)
	{
		fd_in = get_infile();
		fd_out = get_outfile();
	}
}
