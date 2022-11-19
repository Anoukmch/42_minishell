#include "../../../includes/minishell.h"

int	define_exit_code(t_child *child, t_exec *exec)
{
	long long int	buffer;
	bool			istoobig;
	int				status;

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
		{
			exec->hasfreed = true;
			return (perror_return_status("exit: too many arguments", 1));
		}
	}
	// free_struct(child, exec, lex); /* Leaks if I dont free all child ? */
	// free_env(env);
	exit(status);
	return (0);
}

int	command_exit(t_child *child, t_exec *exec, t_env *env, t_lex *lex)
{
	if (exec->nbr_process == 1 && isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (child->parser_cmd[1])
		define_exit_code(child, exec);
	else if (!child->parser_cmd[1])
	{
		if (!env || !lex)
			printf("Test");
		// free_struct(child, exec, lex);
		// free_env(env);
		exit(g_exit_code % 256);
	}
	return (0);
}
