
#include "../../includes/minishell.h"

int open_outfile(t_child *child, int nbr_elements)
{
	int i;

	i = 0;
	while (child->parser_redirect_output[i])
	{
		if (!ft_strcmp(child->parser_redirect_output[i], ">"))
		{
			child->fd_out = open(child->parser_redirect_output[i + 1],
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (child->fd_out < 0)
				return (perror_return("Error outfile :"));
			if (i < nbr_elements - 2)
				close(child->fd_out);
		}
		else if (!ft_strcmp(child->parser_redirect_output[i], ">>"))
		{
			child->fd_out = open(child->parser_redirect_output[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (child->fd_out < 0)
				return (perror_return("Error outfile :"));
			if (i < nbr_elements - 2)
				close(child->fd_out);
		}
		i += 2;
	}
	return (0);
}

int	get_outfile(t_child *child)
{
	int	nbr_elements;

	nbr_elements = 0;
	if (child->parser_redirect_output[0] == NULL)
		return (0);
	while (child->parser_redirect_output[nbr_elements])
		nbr_elements++;
	if (open_outfile(child, nbr_elements))
		return (1);
	return (0);
}

int	get_infile(t_child *child)
{
	int	i;
	int	nbr_elements;
	int	tmp;

	i = 0;
	nbr_elements = 0;
	if (child->parser_redirect_input[0] == NULL)
		return (0);
	while (child->parser_redirect_input[nbr_elements])
		nbr_elements++;
	while (child->parser_redirect_input[i])
	{
		if (!ft_strcmp(child->parser_redirect_input[i], "<"))
		{
			tmp = open(child->parser_redirect_input[i + 1], O_RDONLY);
			if (tmp < 0)
				return (perror_return("Error infile :"));
			if (i < nbr_elements - 2)
				close(tmp);
			else
				child->fd_in = tmp;
		}
		i += 2;
	}
    return (0);
}

int	switch_put(t_child *child, t_exec *exec)
{
	if (child->parser_redirect_input[0] != NULL)
	{
		if (dup2(child->fd_in, STDIN_FILENO) < 0)
			perror_exit_child("Error file_in");
	}
	else if (child->parser_redirect_input[0] == NULL && child->id != 0)
	{
		if (dup2(exec->buffer[0], STDIN_FILENO) < 0)
			perror_exit_child("Error piping");
    }
	if (child->parser_redirect_output[0] != NULL)
	{
		if (dup2(child->fd_out, STDOUT_FILENO) < 0)
			perror_exit_child("Error file_out");
	}
	else if (child->parser_redirect_output[0] == NULL && child->id != (exec->nbr_process - 1))
	{
		if (dup2(exec->end[1], STDOUT_FILENO) < 0)
			perror_exit_child("Error piping");
	}
	return (0);
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
	if (child->parser_redirect_input[0])
		close(child->fd_in);
	if (child->parser_redirect_output[0])
		close(child->fd_out);
	if (exec->isheredoc == 1)
		unlink("heredoc");
}

void	env_command(t_child *child, t_env *env)
{
	if (child->command == NULL)
		exit(127); /* Is it necessary to print a msg ? */
	if (execve(child->command, child->parser_cmd, env->envp_bis) < 0)
		perror_exit_child("execve command failed");
}

int	builtin_command(t_child *child, t_exec *exec, t_env *env)
{
	if (!ft_strcmp(child->command, "pwd"))
		return (command_pwd());
	else if (!ft_strcmp(child->command, "echo"))
		return (command_echo(child));
	else if (!ft_strcmp(child->command, "cd"))
		return (command_cd(child));
	else if (!ft_strcmp(child->command, "exit"))
		return (command_exit(child, exec));
	else if (!ft_strcmp(child->command, "export"))
		return (command_export(child, env));
	else if (!ft_strcmp(child->command, "unset"))
		return (command_unset(child, env));
	else if (!ft_strcmp(child->command, "env"))
		return (command_env(env));
	return (1);
}

int	single_builtin(t_child *child, t_exec *exec, t_env *env)
{
	int	infd_tmp;
	int	outfd_tmp;

	infd_tmp = dup(STDIN_FILENO);
	outfd_tmp = dup(STDOUT_FILENO);
	if (get_infile(child))
		return (1);
	if (get_outfile(child))
		return (1);
	if (child->parser_redirect_input[0] != NULL)
	{
		dup2(child->fd_in, STDIN_FILENO);
		close(child->fd_in);
	}
	if (child->parser_redirect_output[0] != NULL)
	{
		dup2(child->fd_out, STDOUT_FILENO);
		close(child->fd_out);
	}
	if (builtin_command(child, exec, env))
		return (1);
	dup2(infd_tmp, STDIN_FILENO);
	dup2(outfd_tmp, STDOUT_FILENO);
	return (0);
}

int	child_exec(t_child *child, t_exec *exec, t_env *env)
{
	if (exec->nbr_process > 1 && child->id != (exec->nbr_process - 1))
	{
		if (pipe(exec->end) < 0)
			return (1);
	}
	exec->last_pid = fork();
	if (exec->last_pid < 0)
		return (1);
	else if (exec->last_pid == 0)
	{
		if (get_outfile(child))
			exit(1);
		if (get_infile(child))
			exit(1);
		switch_put(child, exec);
		close_pipe(exec, child);
		if (child->isbuiltin == true)
		{
			if (builtin_command(child, exec, env))
				exit (1);
			exit(0);
        }
		else
			env_command(child, env);
	}
	if (child->id != 0)
		close(exec->buffer[0]);
	if (child->id != (exec->nbr_process - 1))
		close(exec->end[1]);
	exec->buffer[0] = exec->end[0];
	return (0);
}

int	processes(t_child *child, t_exec *exec, t_env *env)
{
	if (exec->nbr_process == 1 && child->isbuiltin == true)
	{
		if (single_builtin(child, exec, env))
			return (1);
	}
	else
	{
		if (child_exec(child, exec, env))
			return (1);
	}
	return (0);
}
