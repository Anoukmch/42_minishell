/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:22:48 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/22 15:22:49 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	check_var(t_child *child, t_env *env, int i)
{
	if (child->heredoc_quotes == 0
		&& ft_strcmp(child->heredoc_line, child->parser_redirect_input[i + 1]))
	{
		if (ft_strchr(child->heredoc_line, '$') != NULL)
		{
			child->heredoc_line = handle_var_hd(child->heredoc_line, env);
			if (!child->heredoc_line)
				return (1);
		}
	}
	return (0);
}

int	heredoc_set_up(t_child *child, int i, char **temp)
{
	child->heredoc_line = NULL;
	child->file = open(child->file_buff, O_CREAT | O_WRONLY
			| O_TRUNC, 0644);
	if (child->file < 0)
		return (-1);
	*temp = ft_strjoin(child->parser_redirect_input[i + 1], "\n");
	if (!*temp)
	{
		unlink(child->file_buff);
		return (-1);
	}
	child->set_stdin_back = dup(STDIN_FILENO);
	return (0);
}

int	here_doc(t_child *child, int i, int nbr_elements, t_env *env)
{
	char	*temp;

	if (heredoc_set_up(child, i, &temp) == -1)
		return (1);
	while (ft_strcmp(child->heredoc_line, temp))
	{
		handle_signals_heredoc();
		if (i == nbr_elements - 2 && child->heredoc_line)
			ft_putstr_fd(child->heredoc_line, child->file);
		free(child->heredoc_line);
		child->heredoc_line = readline("> ");
		signal(SIGINT, SIG_IGN);
		if (!child->heredoc_line)
			return (line_null_hd(child, temp));
		else
		{
			if (check_var(child, env, i))
				return (1);
		}
		child->heredoc_line = ft_strapp(child->heredoc_line, "\n");
	}
	return (clean_heredoc(child, temp, i, nbr_elements));
}

int	open_heredoc(t_child *child, t_exec *exec, t_env *env)
{
	int	i;
	int	nbr_elements;

	i = 0;
	nbr_elements = 0;
	while (child->parser_redirect_input[nbr_elements])
		nbr_elements++;
	while (child->parser_redirect_input[i])
	{
		if (!ft_strcmp(child->parser_redirect_input[i], "<<"))
		{
			if (here_doc(child, i, nbr_elements, env))
				return (1);
			else if (i == nbr_elements - 2)
			{
				child->fd_in = open(child->file_buff, O_RDONLY);
				if (child->fd_in < 0)
					return (perror_return_status(NULL, "Error heredoc : ",
							1));
				exec->isheredoc = 1;
			}
		}
		i += 2;
	}
	return (0);
}

int	get_heredoc(t_child **child, t_exec *exec, t_env *env)
{
	int	i;

	i = 0;
	while (child[i])
	{
		if (child[i]->parser_redirect_input[0] != NULL)
		{
			if (open_heredoc(child[i], exec, env))
				return (1);
		}
		i++;
	}
	return (0);
}
