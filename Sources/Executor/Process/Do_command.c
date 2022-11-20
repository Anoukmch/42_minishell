#include "../../../includes/minishell.h"

void	env_command(t_child *child, t_env *env)
{
	if (child->command == NULL)
		perror_exit_status("command not found", 127);
	if (execve(child->command, child->parser_cmd, env->envp_bis) < 0)
		perror_exit_status("Execve command failed", 126);
}

int	builtin_command(t_child *child, t_exec *exec, t_env *env, t_lex	*lex)
{
	if (!ft_strcmp(child->command, "pwd"))
		return (command_pwd());
	else if (!ft_strcmp(child->command, "echo"))
		return (command_echo(child));
	else if (!ft_strcmp(child->command, "cd"))
		return (command_cd(child, env));
	else if (!ft_strcmp(child->command, "exit"))
		return (command_exit(child, exec, env, lex));
	else if (!ft_strcmp(child->command, "export"))
		return (command_export(child, env));
	else if (!ft_strcmp(child->command, "unset"))
		return (command_unset(child, env));
	else if (!ft_strcmp(child->command, "env"))
		return (command_env(env));
	return (1);
}
