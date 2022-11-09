/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:00:52 by amechain          #+#    #+#             */
/*   Updated: 2022/11/09 14:42:18 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_atoilong(long long int *buffer, const char *str)
{
	char			*s;
	unsigned long long	res;
	int				sign;
	int				c;

	s = (char *)str;
	c = 0;
	sign = 1;
	res = 0;
	while ((s[c] >= '\t' && s[c] <= '\r') || (s[c] == ' '))
		c++;
	if (s[c] == '-')
	{
		sign = -1;
		c++;
	}
	else if (s[c] == '+')
		c++;
	while (s[c] >= '0' && s[c] <= '9')
	{
		res = (res * 10) + (s[c] - '0');
		c++;
	}
	if ((res == ((unsigned long long)LLONG_MAX + 1) && sign == 1) || res > ((unsigned long long)LLONG_MAX + 1))
		return(true);
	*buffer = (long long int)res * sign;
	return (false);
}

void delete_quotes(char **cmd)
{
	*cmd = ft_strtrim(*cmd, "\"");
	if (!*cmd)
		errorexit("delete double quote string allocation fail");
	*cmd = ft_strtrim(*cmd, "'");
	if (!*cmd)
		errorexit("delete single quote string allocation fail");
}

/* /!\/!\/!\ Are we already checking these in the parser ? /!\/!\/!\ */

// void	check_args(t_child *child) /* Are we already checking these in the parser ? */
// {
// 	int i;
// 	int j;

// 	i = 1;
// 	j = 0;
// 	while(child->parser_cmd[i])
// 	{
// 		while (child->parser_cmd[i][j])
// 		{
// 			if (child->parser_cmd[i][j] == '(' || child->parser_cmd[i][j] == ')'
// 				|| child->parser_cmd[i][j] == '<' || child->parser_cmd[i][j] == '>')
// 				errorexit("Unexpected token");
// 			j++;
// 		}
// }

void	command_echo(t_child *child)
{
	int	i;
	bool newline;
	/* Handle echo in lower and upper case, every single letter */
	i = 1;
	newline = true;
	while (child->parser_cmd[i])
		delete_quotes(&child->parser_cmd[i++]);
	i = 1;
	while (child->parser_cmd[i] != NULL && !ft_strcmp(child->parser_cmd[i], "-n"))
	{
		newline = false;
		i++;
	}
	while (child->parser_cmd[i])
	{
		if (!ft_strcmp(child->parser_cmd[1], "~"))
			ft_putstr_fd(getenv("HOME"), child->fd_out);
		else
			ft_putstr_fd(child->parser_cmd[i], child->fd_out);
		if (child->parser_cmd[i + 1] != NULL)
			ft_putstr_fd(" ", child->fd_out);
		i++;
	}
	if (newline == true)
		ft_putstr_fd("\n", child->fd_out);
}

/* cd with only a relative or absolute path */

void	command_cd(t_child *child)
{
	if (child->parser_cmd[1] != NULL)
		delete_quotes(&child->parser_cmd[1]);
	if (child->parser_cmd[1] == NULL || !ft_strcmp(child->parser_cmd[1], "~"))
	{
		if (chdir(getenv("HOME")) != 0)
			errorexit("No such file or directory");
	}
	else
	{
		if (chdir(child->parser_cmd[1]) != 0)
			errorexit("No such file or directory");
	}
}

/* pwd with no options */

void	command_pwd(void)
{
	char *s;
	s = getcwd(NULL, 0);
	if (!s)
		errorexit("Get current path fail");
	ft_printf("%s\n", s);
}

/* export with no options */

// void	command_export()
// {

// }

/* unset with no options */

// void	command_unset()
// {

// }

/* env with no options or arguments */

void	command_env(t_exec *exec)
{
	int	i;

	i = 0;
	while(exec->envp_bis[i])
	{
		if (ft_strchr(exec->envp_bis[i], '=') != NULL)
			ft_printf("%s\n", exec->envp_bis[i]);
		i++;
	}
}

/* exit with no options */

void	command_exit(t_child *child)
{
	long long int	buffer;
	bool			istoobig;
	int 			status;
	int				i;

	i = 0;
	status = 0;
	ft_putstr_fd("exit\n", 1);
	if (child->parser_cmd[1] != NULL)
	{
		if (child->parser_cmd[1][i] == '-')
			i++;
		while (child->parser_cmd[1][i])
		{
			if (child->parser_cmd[1][i] < 48 || child->parser_cmd[1][i] > 57)
				errorexit("Numeric argument required");
			i++;
		}
		istoobig = ft_atoilong(&buffer, child->parser_cmd[1]);
		if (istoobig == true)
			errorexit("Exit code too long or too short");
		status = buffer % 256;
	}
	if (child->no_cmd_opt > 2)
		errorexit("Too many arguments for exit function"); /* This shouldn't exit but just return to a newline */
	exit(status);
}
