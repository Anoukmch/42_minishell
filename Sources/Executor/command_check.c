

#include "../../includes/minishell.h"

static int	check_builtins_other(t_child *child)
{
	if (ft_strncmp("echo", child->parser_cmd[0], 5) == 0)
	{
		child->command = ft_strdup("echo");
		if (!child->command)
			return (1);
	}
	else if (ft_strncmp("cd", child->parser_cmd[0], 3) == 0)
	{
		child->command = ft_strdup("cd");
		if (!child->command)
			return (1);
	}
	else if (ft_strncmp("pwd", child->parser_cmd[0], 4) == 0)
	{
		child->command = ft_strdup("pwd");
		if (!child->command)
			return (1);
	}
	else if (ft_strncmp("exit", child->parser_cmd[0], 5) == 0)
	{
		child->command = ft_strdup("exit");
		if (!child->command)
			return (1);
	}
	return (0);
}

static int	check_builtins_env(t_child *child)
{
	if (ft_strncmp("export", child->parser_cmd[0], 7) == 0)
	{
		child->command = ft_strdup("export");
		if (!child->command)
			return (1);
	}
	else if (ft_strncmp("unset", child->parser_cmd[0], 6) == 0)
	{
		child->command = ft_strdup("unset");
		if (!child->command)
			return (1);
	}
	else if (ft_strncmp("env", child->parser_cmd[0], 4) == 0)
	{
		child->command = ft_strdup("env");
		if (!child->command)
			return (1);
	}
	return (0);
}

// *** CHECK ABSOLUTE PATH ***
static void	check_existing_path(t_env *env, t_child *child)
{
	if (env->envp_bis == NULL || env->envp_path == NULL
		|| ft_strchr(child->parser_cmd[0], '/') != NULL)
	{
		child->command = ft_strdup(child->parser_cmd[0]);
		if (access(child->command, 0) == 0)
			return ;
		else
			child->command = NULL;
	}
}

// *** FIND PATH TO COMMAND ***
static void	find_command_path(t_env *env, t_child *child)
{
	int	i;

	i = 0;
	while (env->envp_bis && env->envp_path[i])
	{
		child->command = ft_strjoin(env->envp_path[i],
				child->parser_cmd[0]);
		if (!child->command)
			return ;
		if (access(child->command, 0) == 0)
			return ;
		free(child->command);
		i++;
	}
	perror(NULL);
	child->command = NULL;
}

// *** NO PATH FOUND OR ENVIRONMENT DISABLED ***
static int	command_not_found(t_child *child, t_env *env)
{
	if (env->envp_bis == NULL || env->envp_path == NULL
		|| ft_strchr(child->parser_cmd[0], '/') != NULL)
		return (0);
	return (0);
}

// *** 1. CHECK CURRENT DIRECTORY AS PATH IF ITS NOT AN ABSOLUTE PATH ***
// *** 2. CHECK ABSOLUTE PATH ***
// *** 3. FIND PATH FOR COMMAND ***
// *** 4. PATH NOT FOUND & ENVIRONMENT DISABLED ***
static int	check_path(t_child *child, t_env *env)
{
	if (!ft_strchr(child->parser_cmd[0], '/')
		&& (env->envp_path == NULL || env->envp_bis == NULL))
	{
		child->command = ft_strjoin(getcwd(NULL, 0), "/");
		child->command = ft_strjoin(child->command,
				child->parser_cmd[0]);
		if (!child->command)
			return(0);
		if (access(child->command, 0) == 0)
			return (0);
		return(0);
	}
	if (ft_strchr(child->parser_cmd[0], '/'))
	{
		check_existing_path(env, child);
		if (child->command)
			return (0);
	}
	else
		find_command_path(env, child);
	if (child->command)
		return (0);
	if (command_not_found(child, env))
		return (0);
	return (0);
}

// CHECK IF BUILT-IN
// IF NOT BUILT-IN --> CHECK ABSOLUTE PATH/ FIND PATH
static int	check_commands(t_child *child, t_env *env)
{
	if (!ft_strcmp(child->parser_cmd[0], ""))
		return (0);
	if (check_builtins_env(child)
		|| check_builtins_other(child))
		return (1);
	if (child->command)
		child->isbuiltin = true;
	if (child->command == NULL)
	{
		if (check_path(child, env))
			return (0);
	}
	return (0);
}

// CHECK COMMAND OF EVERY PROCESS
int	command_path(t_child *child, t_env *env)
{
	if (child->parser_cmd[0])
	{
		if (check_commands(child, env))
			return (1);
	}
	return (0);
}
