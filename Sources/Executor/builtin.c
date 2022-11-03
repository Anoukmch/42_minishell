/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:00:52 by amechain          #+#    #+#             */
/*   Updated: 2022/11/03 18:51:21 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* echo with option -n */

void	command_echo(t_child *child)
{
	int	i;
	int j;

	i = 1;
	j = 0;
	if (child->parser_cmd[1] == NULL)
	{
		if (child->fd_out)
			write(child->fd, '\n', 1);
		return ;
	}
	while(child->parser_cmd[i])
	{
		while (child->parser_cmd[i][j]) /* Are they null terminated ? */
		{
			if (child->parser_cmd[i][j] == '(' || child->parser_cmd[i][j] == ')'
				|| child->parser_cmd[i][j] == '<' || child->parser_cmd[i][j] == '>')
				errorexit("Unexpected token");
			j++;
		}
		ft_putstr_fd(child->parser_cmd[i], child->fd_out);
		i++;
	}
	echo ~ : getenv("HOME")
	/* if nothing then print nothing */
}

/* cd with only a relative or absolute path */

void	command_cd(t_child *child)
{
	int	i;
	int j;

	i = 1;
	j = 0;
	while(child->parser_cmd[i])
	{
		while (child->parser_cmd[i][j]) /* Are they null terminated ? */
		{
			if (child->parser_cmd[i][j] == '(' || child->parser_cmd[i][j] == ')'
				|| child->parser_cmd[i][j] == '<' || child->parser_cmd[i][j] == '>')
				errorexit("Unexpected token");
			j++;
		}
		i++;
	}
	if (child->parser_cmd[1] == NULL || child->parser_cmd[1] == '~')
	{
		if (chdir(getenv("HOME")) != 0)
			errorexit("Chdir fail");
	}
	else
	{
		if (chdir(child->parser_cmd[1]) != 0)
			errorexit("Chdir fail");
	}
}

/* pwd with no options */

void	command_pwd(t_child *child)
{
	char *s;
	int	i;
	int j;

	i = 1;
	j = 0;
	while(child->parser_cmd[i])
	{
		while (child->parser_cmd[i][j]) /* Are they null terminated ? */
		{
			if (child->parser_cmd[i][j] == '(' || child->parser_cmd[i][j] == ')'
				|| child->parser_cmd[i][j] == '<' || child->parser_cmd[i][j] == '>')
				errorexit("Unexpected token");
			j++;
		}
		i++;
	}
	s = getcwd(NULL, 0);
	if (!s)
		errorexit("Get current path fail");
	ft_printf("%s\n", s);
}

/* export with no options */

void	command_export()
{

}

/* unset with no options */

void	command_unset()
{

}

/* env with no options or arguments */

void	command_env()
{

}

/* exit with no options */

void	command_exit()
{
	exit(0);
	/* Exit code min 0 max 255, modulo 256 */
	/* Check for all the edge cases */
	/* Echo "exit" ? */
}
