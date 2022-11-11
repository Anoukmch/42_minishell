/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:43:43 by jmatheis          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/11/11 16:44:22 by jmatheis         ###   ########.fr       */
=======
/*   Updated: 2022/11/11 13:09:59 by amechain         ###   ########.fr       */
>>>>>>> 5d66a72fd8cd72ff71501d6bcb9afd3df04ef089
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

// exec->heredoc = 1 --> QUOTES --> no expansion of variables
// exec->heredoc = 0 --> NO QUOTES --> expansion of variables
// DELETE QUOTES & STORE INFORMATION SOMEWHERE
void	here_doc(char *limiter, int i, int nbr_elements)
{
	int		file;
	char	*line;
	char	*temp;

	file = open("heredoc", O_CREAT | O_WRONLY
			| O_TRUNC, 0644);
	if (file < 0)
		errorexit("Open heredoc failed");
<<<<<<< HEAD
	// if (child[k]-->heredoc_quotes == 0)
	//  expand variables in heredoc
	// if (child[k]-->heredoc_quotes == 1)
	//  DO NOT expand variables in heredoc	
=======
	//delete_quotes(&limiter);
>>>>>>> 5d66a72fd8cd72ff71501d6bcb9afd3df04ef089
	temp = ft_strjoin(limiter, "\n");
	ft_printf("Heredoc>");
	line = get_next_line(STDIN_FILENO);
	if (!line)
		ft_printf("Get_next_line failed");
	while (ft_strncmp(line, temp, (ft_strlen(temp) + 1)))
	{
		if (i == nbr_elements - 2)
			ft_putstr_fd(line, file);
		free(line);
		ft_printf("Heredoc>");
		line = get_next_line(STDIN_FILENO);
		if (!line)
			errorexit("Get_next_line failed");
	}
	free(line);
	free(temp);
	close(file);
	if (i < nbr_elements - 2)
		unlink("heredoc");
}

void	get_outfile(t_child *child)
{
	int	i;
	int nbr_elements;

	i = 0;
	nbr_elements = 0;
	while (child->parser_redirect_output[nbr_elements])
		nbr_elements++;
	while (child->parser_redirect_output[i])
	{
		if (!ft_strcmp(child->parser_redirect_output[i], ">"))
		{
			child->fd_out = open(child->parser_redirect_output[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (child->fd_out < 0)
				errorexit("Open outfile failed");
			if (i < nbr_elements - 2)
				close(child->fd_out);
		}
		else if (!ft_strcmp(child->parser_redirect_output[i], "<<"))
		{
			child->fd_out = open(child->parser_redirect_output[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (child->fd_out < 0)
				errorexit("Open outfile failed");
			if (i < nbr_elements - 2)
				close(child->fd_out);
		}
		i += 2;
	}
}

void	get_infile(t_child *child, t_exec *exec)
{
	int	i;
	int nbr_elements;

	i = 0;
	nbr_elements = 0;
	while (child->parser_redirect_input[nbr_elements])
		nbr_elements++;
	while (child->parser_redirect_input[i])
	{
		if (!ft_strcmp(child->parser_redirect_input[i], "<"))
		{
			child->fd_in = open(child->parser_redirect_input[i + 1], O_RDONLY);
			if (child->fd_in < 0)
				errorexit("Open infile failed");
			if (i < nbr_elements - 2)
				close(child->fd_in);
		}
		else if (!ft_strcmp(child->parser_redirect_input[i], "<<"))
		{
			here_doc(child->parser_redirect_input[i + 1], i, nbr_elements);
			if (i == nbr_elements - 2)
			{
				child->fd_in = open("heredoc", O_RDONLY);
				if (child->fd_in < 0)
					errorexit("Open infile heredoc failed");
				exec->isheredoc = 1;
			}
		}
		i += 2;
	}
}

void	switch_put(t_child *child, t_exec *exec)
{
	if (child->parser_redirect_input[0] != NULL)
	{
		if (dup2(child->fd_in, STDIN_FILENO) < 0)
			errorexit("Dup2 infile failed");
	}
	else if (child->parser_redirect_input[0] == NULL && child->id != 0)
	{
		if (dup2(exec->buffer[0], STDIN_FILENO) < 0)
			errorexit("Dup2 infile failed");
	}
	if (child->parser_redirect_output[0] != NULL)
	{
		if (dup2(child->fd_out, STDOUT_FILENO) < 0)
			errorexit("Dup2 outfile failed");
	}
	else if (child->parser_redirect_output[0] == NULL && child->id != (exec->nbr_process - 1))
	{
		if (dup2(exec->end[1], STDOUT_FILENO) < 0)
			errorexit("Dup2 outfile failed");
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
	if (exec->isheredoc == 1)
		unlink("heredoc");
}

void	builtin_command(t_child *child, t_exec *exec)
{
	if (!ft_strcmp(child->command, "pwd"))
		command_pwd(exec);
	else if (!ft_strcmp(child->command, "echo"))
		command_echo(child, exec);
	else if (!ft_strcmp(child->command, "cd"))
		command_cd(child, exec);
	else if (!ft_strcmp(child->command, "exit"))
		command_exit(child, exec);
	else if (!ft_strcmp(child->command, "export"))
		command_export(child, exec);
	else if (!ft_strcmp(child->command, "unset"))
		command_unset(child, exec);
	else if (!ft_strcmp(child->command, "env"))
		command_env(exec);
	else if (execve(child->command, child->parser_cmd, exec->envp_bis) < 0)
		errorexit("execve fail");
}

void	processes(t_child *child, t_exec *exec)
{
	if (exec->nbr_process == 1)
	{
		builtin_command(child, exec);
		return ;
	}
	if (exec->nbr_process > 1 && child->id != (exec->nbr_process - 1))
	{
		if (pipe(exec->end) < 0)
			errorexit("Pipe fail");
	}
	exec->last_pid = fork();
	if (exec->last_pid < 0)
		errorexit("Fork fail");
	else if (exec->last_pid == 0)
	{
		if (child->parser_redirect_input[0] != NULL)
			get_infile(child, exec);
		if (child->parser_redirect_output[0] != NULL)
			get_outfile(child);
		switch_put(child, exec);
		close_pipe(exec, child);
		builtin_command(child, exec);
	}
	if (child->id != 0)
		close(exec->buffer[0]);
	if (child->id != (exec->nbr_process - 1))
		close(exec->end[1]);
	exec->buffer[0] = exec->end[0];
}


