#include "../../../includes/minishell.h"

void	exit_exit_builtin(t_child *child, t_exec *exec, t_env *env)
{
	free_child(child, exec, NULL);
	free_env(env);
	rl_clear_history();
	perror_exit_status(NULL, "exit: numeric argument required", 255);
}

int	define_exit_code(t_child *child, t_exec *exec, t_env *env)
{
	long long int	buffer;
	bool			istoobig;
	int				status;

	status = 0;
	if (is_only_digits(child->parser_cmd[1])
		|| child->parser_cmd[1][0] == '\0')
		exit_exit_builtin(child, exec, env);
	istoobig = ft_atoilong(&buffer, child->parser_cmd[1]);
	if (istoobig == true)
		exit_exit_builtin(child, exec, env);
	status = buffer % 256;
	if (child->no_cmd_opt > 2)
	{
		if (exec->nbr_process > 1)
			perror_exit_status(NULL, "exit: too many arguments", 1);
		else
			return (perror_return_status(NULL, "exit: too many arguments", 1));
	}
	if (exec->nbr_process > 1)
		exit(status);
	else
		exec->need_exit = true;
	g_exit_code = status;
	return (0);
}

int	command_exit(t_child *child, t_exec *exec, t_env *env)
{
	if (exec->nbr_process == 1 && isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (child->parser_cmd[1])
		define_exit_code(child, exec, env);
	else if (!child->parser_cmd[1])
	{
		if (exec->nbr_process > 1)
			exit(0);
		else
			exec->need_exit = true;
	}
	return (0);
}
