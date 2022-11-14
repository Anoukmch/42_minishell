

#include "../../includes/minishell.h"

static int	check_builtins_other(t_lex *lex, t_child **child)
{
	if (ft_strncmp("echo", child[lex->iter]->parser_cmd[0], 5) == 0)
	{
		child[lex->iter]->command = ft_strdup("echo");
		if (!child[lex->iter]->command)
			return (1);
	}
	else if (ft_strncmp("cd", child[lex->iter]->parser_cmd[0], 3) == 0)
	{
		child[lex->iter]->command = ft_strdup("cd");
		if (!child[lex->iter]->command)
			return (1);
	}
	else if (ft_strncmp("pwd", child[lex->iter]->parser_cmd[0], 4) == 0)
	{
		child[lex->iter]->command = ft_strdup("pwd");
		if (!child[lex->iter]->command)
			return (1);
	}
	else if (ft_strncmp("exit", child[lex->iter]->parser_cmd[0], 5) == 0)
	{
		child[lex->iter]->command = ft_strdup("exit");
		if (!child[lex->iter]->command)
			return (1);
	}
	return (0);
}

static int	check_builtins_env(t_lex *lex, t_child **child)
{
	if (ft_strncmp("export", child[lex->iter]->parser_cmd[0], 7) == 0)
	{
		child[lex->iter]->command = ft_strdup("export");
		if (!child[lex->iter]->command)
			return (1);
	}
	else if (ft_strncmp("unset", child[lex->iter]->parser_cmd[0], 6) == 0)
	{
		child[lex->iter]->command = ft_strdup("unset");
		if (!child[lex->iter]->command)
			return (1);
	}
	else if (ft_strncmp("env", child[lex->iter]->parser_cmd[0], 4) == 0)
	{
		child[lex->iter]->command = ft_strdup("env");
	else if (ft_strncmp("exit", child[lex->iter]->parser_cmd[0], 5) == 0)
		child[lex->iter]->command = ft_strdup("exit");
	/* Protect MALLOC return */
}

// *** CHECK ABSOLUTE PATH ***
static void	check_existing_path(t_env *env, t_child **child, t_lex *lex)
{
	if (env->envp_bis == NULL || env->envp_path == NULL
		|| ft_strchr(child[lex->iter]->parser_cmd[0], '/') != NULL)
	{
		child[lex->iter]->command = ft_strdup(child[lex->iter]->parser_cmd[0]);
		if (access(child[lex->iter]->command, 0) == 0)
			return ;
		else
			child[lex->iter]->command = NULL;
	}
}

// *** FIND PATH TO COMMAND ***
static void	find_command_path(t_env *env, t_child **child, t_lex *lex)
{
	int	i;

	i = 0;
	while (env->envp_bis && env->envp_path[i])
	{
		child[lex->iter]->command = ft_strjoin(env->envp_path[i],
				child[lex->iter]->parser_cmd[0]);
		if (!child[lex->iter]->command)
			return ;
		if (access(child[lex->iter]->command, 0) == 0)
			return ;
		free(child[lex->iter]->command);
		i++;
	}
	child[lex->iter]->command = NULL;
}

// *** NO PATH FOUND OR ENVIRONMENT DISABLED ***
static int	command_not_found(t_child **child, t_env *env, t_lex *lex)
{
	if (env->envp_bis == NULL || env->envp_path == NULL
		|| ft_strchr(child[lex->iter]->parser_cmd[0], '/') != NULL)
		return (1);
	return (0);
}

// *** 1. CHECK CURRENT DIRECTORY AS PATH IF ITS NOT AN ABSOLUTE PATH ***
// *** 2. CHECK ABSOLUTE PATH ***
// *** 3. FIND PATH FOR COMMAND ***
// *** 4. PATH NOT FOUND & ENVIRONMENT DISABLED ***
static int	check_path(t_lex *lex, t_child **child, t_env *env)
{
	if (!ft_strchr(child[lex->iter]->parser_cmd[0], '/')
		&& (env->envp_path == NULL || env->envp_bis == NULL))
	{
		child[lex->iter]->command = ft_strjoin(getcwd(NULL, 0), "/");
		child[lex->iter]->command = ft_strjoin(child[lex->iter]->command,
				child[lex->iter]->parser_cmd[0]);
		if (!child[lex->iter]->command)
			return(1);
		if (access(child[lex->iter]->command, 0) == 0)
			return (0);
		return(1);
	}
	if (ft_strchr(child[lex->iter]->parser_cmd[0], '/'))
	{
		check_existing_path(exec, child, lex);
		if (child[lex->iter]->command)
			return (0);
	}
	else
		find_command_path(exec, child, lex);
	if (child[lex->iter]->command)
		return (0);
	if (command_not_found(child, exec, lex))
		return (1);
	return (1);
}

// CHECK IF BUILT-IN
// IF NOT BUILT-IN --> CHECK ABSOLUTE PATH/ FIND PATH
static int	check_commands(t_lex *lex, t_child **child, t_env *env)
{
	if (!ft_strcmp(child[lex->iter]->parser_cmd[0], ""))
		return (1);
	check_builtins(lex, child);
	if (child[lex->iter]->command)
		child[lex->iter]->isbuiltin = true;
	if (child[lex->iter]->command == NULL)
	{
		if (check_path(lex, child, exec))
			return (1);
	}
	return (0);
}

// CHECK COMMAND OF EVERY PROCESS
int	command_path(t_lex *lex, t_child **child, t_env *env)
{
	lex->iter = 0;
	while (child[lex->iter])
	{
		if (child[lex->iter]->parser_cmd[0])
		{
			if (check_commands(lex, child, exec))
				return (1);
		}
		lex->iter++;
	}
	return (0);
}
