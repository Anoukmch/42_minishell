
#include "../../includes/minishell.h"

bool	ft_atoilong(long long int *buffer, char *s)
{
	unsigned long long	res;
	int					sign;
	int					c;

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
		res = (res * 10) + (s[c++] - '0');
	if ((res == ((unsigned long long)LLONG_MAX + 1) && sign == 1)
		|| res > ((unsigned long long)LLONG_MAX + 1))
		return (true);
	*buffer = (long long int)res * sign;
	return (false);
}

int	command_echo(t_child *child)
{
	int		i;
	bool	newline;

	i = 1;
	newline = true;
	while (child->parser_cmd[i] != NULL
		&& !ft_strcmp(child->parser_cmd[i], "-n"))
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
	return (0);
}

int	command_cd(t_child *child)
{
	if (child->parser_cmd[1] == NULL || !ft_strcmp(child->parser_cmd[1], "~"))
	{
		if (chdir(getenv("HOME")) != 0)
			return (perror_return_status(NULL, 1));
	}
	else
	{
		if (child->parser_cmd[1][0] != '\0' && chdir(child->parser_cmd[1]) != 0)
			return (perror_return_status(NULL, 1));
	}
	return (0);
}

int	get_position_of_variable(t_env *env, char *variable)
{
	int	i;

	i = 0;
	while (env->envp_bis[i])
	{
		if (ft_strncmp(env->envp_bis[i], variable, ft_strlen(variable)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	command_pwd(void)
{
	char	*s;

	s = getcwd(NULL, 0);
	if (!s)
		return (1);
	ft_printf("%s\n", s);
	return (0);
}

int	command_env(t_env *env)
{
	int	i;

	i = 0;
	while (env->envp_bis[i])
	{
		if (ft_strchr(env->envp_bis[i], '=') != NULL)
			ft_printf("%s\n", env->envp_bis[i]);
		i++;
	}
	return (0);
}

int	is_only_digits(char *str)
{
	int	i;

	i = 0;
	if ((str[i] == '-' && str[i + 1])
		|| (str[i] == '+' && str[i + 1]))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	define_exit_code(t_child *child, t_exec *exec)
{
	long long int	buffer;
	bool	istoobig;
	int		status;

	status = 0;
	if (is_only_digits(child->parser_cmd[1])
		|| child->parser_cmd[1][0] == '\0')
		perror_exit_status("exit: numeric argument required", 255);
	istoobig = ft_atoilong(&buffer, child->parser_cmd[1]);
	if (istoobig == true)
		perror_exit_status("exit: numeric argument required", 255);
	status = buffer % 256;
	if (child->no_cmd_opt > 2)
	{
		if (exec->nbr_process > 1)
			perror_exit_status("exit: too many arguments", 1);
		else
			return (perror_return_status("exit: too many arguments", 1));
	}
	// free_struct(child, exec, lex);
	// free_env(env);
	exit(status);
}

int	command_exit(t_lex	*lex, t_child *child, t_exec *exec, t_env *env)
{
	if (exec->nbr_process == 1 && isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (child->parser_cmd[1])
		define_exit_code(child, exec);
	else if (!child->parser_cmd[1])
	{
		// free_struct(child, exec, lex);
		// free_env(env);
		exit(g_exit_code % 256);
	}
	return (0);
}
