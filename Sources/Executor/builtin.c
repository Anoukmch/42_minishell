
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

// void delete_quotes(char **cmd)
// {
// 	*cmd = ft_strtrim(*cmd, "\"");
// 	if (!*cmd)
// 		errorexit("delete double quote string allocation fail");
// 	*cmd = ft_strtrim(*cmd, "'");
// 	if (!*cmd)
// 		errorexit("delete single quote string allocation fail");
// }

void	command_echo(t_child *child, t_exec *exec)
{
	int	i;
	bool newline;
	/* Handle echo in lower and upper case, every single letter */
	i = 1;
	newline = true;
	while (child->parser_cmd[i] != NULL && !ft_strcmp(child->parser_cmd[i], "-n"))
	{
		newline = false;
		i++;
	}
	while (child->parser_cmd[i])
	{
		if (!ft_strcmp(child->parser_cmd[1], "~"))
			ft_printf("%s", getenv("HOME"));
		else
			ft_printf("%s", child->parser_cmd[i]);
		if (child->parser_cmd[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	if (newline == true)
		ft_printf("\n");
	if (exec->nbr_process > 1)
		exit(0);
}

/* cd with only a relative or absolute path */

void	command_cd(t_child *child, t_exec *exec)
{
	/* If cd "" , do nothing. Different from having a null argument which means cd HOME */
	if (child->parser_cmd[1] == NULL || !ft_strcmp(child->parser_cmd[1], "~"))
	{
		if (chdir(getenv("HOME")) != 0)
			errorexit("cd: No such file or directory\n");
	}
	else
	{
		if (child->parser_cmd[1][0] != '\0' && chdir(child->parser_cmd[1]) != 0)
		{
			fprintf(stderr, "cd: %s: No such file or directory\n", child->parser_cmd[1]);
			exit(1);
		}
	}
	if (exec->nbr_process > 1)
		exit(0);
}
// 	if (o != -1 && i != -1)
	// {
	// 	exec->envp_bis[o] = ft_strjoin("OLDPWD=", s));
	// }
	// else if (o != -1 && i != -1)
	// {
	// 	// CALL EXPORT FUNCTION
	// 	EXPORT OLDPWD --> ft_strjoin with s
	// }

/* pwd with no options */
int	get_position_of_variable(t_exec *exec, char *variable)
{
	int	i;

	i = 0;
	while (exec->envp_bis[i])
	{
		if (ft_strncmp(exec->envp_bis[i], variable, ft_strlen(variable)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

// OLDPWD?
void	command_pwd(t_exec *exec)
{
	char	*s;

	s = getcwd(NULL, 0);
	if (!s)
		errorexit("Get current path fail");
	ft_printf("%s\n", s);
	if (exec->nbr_process > 1)
		exit(0);
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
	if (exec->nbr_process > 1)
		exit(0);
}

/* exit with no options */

void	command_exit(t_child *child, t_exec *exec)
{
	/* exit "" : the "" shouldnt be remove by lexer */
	long long int	buffer;
	bool			istoobig;
	int 			status;
	int				i;

	i = 0;
	status = 0;
	ft_putstr_fd("exit\n", 1);
	if (child->parser_cmd[1])
	{
		if ((child->parser_cmd[1][i] == '-' && child->parser_cmd[1][i + 1])
			|| (child->parser_cmd[1][i] == '+' && child->parser_cmd[1][i + 1]))
			i++;
		while (child->parser_cmd[1][i] || child->parser_cmd[1][0] == '\0')
		{
			if (child->parser_cmd[1][i] < 48 || child->parser_cmd[1][i] > 57)
			{
				fprintf(stderr, "bash: exit: numeric argument required\n");
				exit(255); /* with which code exit ? 255 ? */
			}
			i++;
		}
		istoobig = ft_atoilong(&buffer, child->parser_cmd[1]);
		if (istoobig == true)
			errorexit("Exit code too long or too short\n");
		status = buffer % 256;
		if (child->no_cmd_opt > 2)
		{
			fprintf(stderr, "bash: exit: too many arguments\n"); /* This shouldn't exit but just return to a newline and exit code == 1 (failure) */
			if (exec->nbr_process > 1)
				exit(1);
			else
				return ;
		}
		exit(status);
	}
	else if (!child->parser_cmd[1])
		exit(exit_code % 256);
}
