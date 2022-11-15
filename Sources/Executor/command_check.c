

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
		if (!child[lex->iter]->command)
			return (1);
	}
	return (0);
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
	// if (!ft_strchr(child[lex->iter]->parser_cmd[0], '/')
	// 	&& (env->envp_path == NULL || env->envp_bis == NULL))
	// {
	// 	child[lex->iter]->command = ft_strjoin(getcwd(NULL, 0), "/");
	// 	child[lex->iter]->command = ft_strjoin(child[lex->iter]->command,
	// 			child[lex->iter]->parser_cmd[0]);
	// 	if (!child[lex->iter]->command)
	// 		return(1);
	// 	if (access(child[lex->iter]->command, 0) == 0)
	// 		return (0);
	// 	return(1);
	// }
static int	get_environment_path(t_child **child, t_env *env)
{
	int	i;

	i = 0;
	if (!env->envp_bis && !ft_strchr(child[lex->iter]->parser_cmd[0], '/'))
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
}

static int	check_path(t_lex *lex, t_child **child, t_env *env)
{

	while(env->envp_bis[i])
	{
		if (!ft_strncmp(env->envp_bis[i], "PATH", 4))
		{
			env->envp_line = ft_strchr(env->envp_bis[i], '/'); //PATH FROM OWN ENVIRONMENT
			break ;
		}
		i++;
	}
	if (!env->envp_line && !ft_strchr(child[lex->iter]->parser_cmd[0], '/'))
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
	else
	{
		env->envp_path = ft_split(env->envp_line, ':');
		i = 0;
		while (env->envp_path[i])
		{
			env->envp_path[i] = ft_strjoin(env->envp_path[i], "/");
			i++;
		}
	}
	if (ft_strchr(child[lex->iter]->parser_cmd[0], '/'))
	{
		check_existing_path(env, child, lex);
		if (child[lex->iter]->command)
			return (0);
	}
	else
		find_command_path(env, child, lex);
	if (child[lex->iter]->command)
		return (0);
	if (command_not_found(child, env, lex))
		return (1);
	return (1);
}

// CHECK IF BUILT-IN
// IF NOT BUILT-IN --> CHECK ABSOLUTE PATH/ FIND PATH
static int	check_commands(t_lex *lex, t_child *child, t_env *env)
{
	if (!ft_strcmp(child->parser_cmd[0], ""))
		return (1);
	if (check_builtins_env(lex, child)
		|| check_builtins_other(lex, child))
		return (1);
	if (child->command)
		child->isbuiltin = true;
	if (child->command == NULL)
	{
		if (check_path(lex, child, env))
			return (1);
	}
	return (0);
}

// CHECK COMMAND OF EVERY PROCESS
int	command_path(t_lex *lex, t_child *child, t_env *env)
{
	if (child->parser_cmd[0])
	{
		if (check_commands(child, env))
			return (1);
	}
	}
	return (0);
}
