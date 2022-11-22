/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:22:57 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/22 15:22:58 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	handle_signals_child(void)
{
	struct termios		te;

	ft_memset(&te, 0, sizeof(te));
	tcgetattr(0, &te);
	te.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &te);
}

int	child_exec_bis(t_child *child, t_exec *exec, t_env *env)
{
	exec->last_pid = fork();
	if (exec->last_pid < 0)
		return (1);
	else if (exec->last_pid == 0)
	{
		handle_signals_child();
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (get_outfile(child))
			exit(1);
		if (get_infile(child))
			exit(1);
		switch_put(child, exec);
		if (close_pipe(exec, child))
			return (1);
		if (child->isbuiltin == true)
		{
			if (builtin_command(child, exec, env))
				exit(1);
			exit(0);
		}
		else
			env_command(child, env);
	}
	return (0);
}

int	child_exec(t_child *child, t_exec *exec, t_env *env)
{
	if (exec->nbr_process > 1 && child->id != (exec->nbr_process - 1))
	{
		if (pipe(exec->end) < 0)
			return (1);
	}
	if (child_exec_bis(child, exec, env))
		return (1);
	if (exec->nbr_process > 1)
	{
		if (child->id != 0)
			close(exec->buffer[0]);
		if (child->id != (exec->nbr_process - 1))
			close(exec->end[1]);
		exec->buffer[0] = exec->end[0];
	}
	return (0);
}
