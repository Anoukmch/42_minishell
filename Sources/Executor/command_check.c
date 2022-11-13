

#include "../../includes/minishell.h"

static void	check_builtins(t_lex *lex, t_child **child)
{
	if (ft_strncmp("echo", child[lex->iter]->parser_cmd[0], 5) == 0)
		child[lex->iter]->command = ft_strdup("echo");
	else if (ft_strncmp("cd", child[lex->iter]->parser_cmd[0], 3) == 0)
		child[lex->iter]->command = ft_strdup("cd");
	else if (ft_strncmp("pwd", child[lex->iter]->parser_cmd[0], 4) == 0)
		child[lex->iter]->command = ft_strdup("pwd");
	else if (ft_strncmp("export", child[lex->iter]->parser_cmd[0], 7) == 0)
		child[lex->iter]->command = ft_strdup("export");
	else if (ft_strncmp("unset", child[lex->iter]->parser_cmd[0], 6) == 0)
		child[lex->iter]->command = ft_strdup("unset");
	else if (ft_strncmp("env", child[lex->iter]->parser_cmd[0], 4) == 0)
		child[lex->iter]->command = ft_strdup("env");
	else if (ft_strncmp("exit", child[lex->iter]->parser_cmd[0], 5) == 0)
		child[lex->iter]->command = ft_strdup("exit");
	/* Proteger les retours MALLOC */
}

static void	check_existing_path(t_exec *exec, t_child **child, t_lex *lex)
{
	if (exec->envp_bis == NULL || exec->envp_path == NULL
		|| ft_strchr(child[lex->iter]->parser_cmd[0], '/') != NULL)
	{
		child[lex->iter]->command = ft_strdup(child[lex->iter]->parser_cmd[0]);
		//printf("TesT COMAMD: %s\n", child[lex->iter]->command);
		if (access(child[lex->iter]->command, 0) == 0)
		{
			return ;
		}
		else
		{
			child[lex->iter]->command = NULL;
			return ;
		}
	}
}

static void	find_command_path(t_exec *exec, t_child **child, t_lex *lex)
{
	int	i;

	i = 0;
	while (exec->envp_bis && exec->envp_path[i])
	{
		//printf("\nrelative path\n");
		child[lex->iter]->command = ft_strjoin(exec->envp_path[i],
				child[lex->iter]->parser_cmd[0]);
		if (!child[lex->iter]->command)
			errorexit("child[lex->iter]->command allocation fail");
		if (access(child[lex->iter]->command, 0) == 0)
			return ; // return (0);
		free(child[lex->iter]->command);
		i++;
	}
	child[lex->iter]->command = NULL;
}

static int	command_not_found(t_child **child, t_exec *exec, t_lex *lex)
{
	if (exec->envp_bis == NULL || exec->envp_path == NULL
		|| ft_strchr(child[lex->iter]->parser_cmd[0], '/') != NULL)
	{
		// CHECK CURRENT PATH
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(child[lex->iter]->parser_cmd[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		//perror(NULL);
		return (1); //return(1);
	}
	return (0);
}

static int	check_path(t_lex *lex, t_child **child, t_exec *exec)
{
	if (!ft_strchr(child[lex->iter]->parser_cmd[0], '/')
		&& (exec->envp_path == NULL || exec->envp_bis == NULL))
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(child[lex->iter]->parser_cmd[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	check_existing_path(exec, child, lex);
	if (child[lex->iter]->command != NULL)
		return (0); // return (0);
	find_command_path(exec, child, lex);
	if (child[lex->iter]->command != NULL)
		return (0);
	if (command_not_found(child, exec, lex) != 0)
		return (1);
	return (1);
}

static int	check_commands(t_lex *lex, t_child **child, t_exec *exec)
{
	if (!ft_strcmp(child[lex->iter]->parser_cmd[0], ""))
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(child[lex->iter]->parser_cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		return (1);
	}
	check_builtins(lex, child);
	if (child[lex->iter]->command)
		child[lex->iter]->isbuiltin = true;
	if (child[lex->iter]->command == NULL)
	{
		if (check_path(lex, child, exec) != 0)
			return (1);

	}
	//printf("CMD PATH: %s\n", child[lex->iter]->command);
	return (0);
}

int	command_path(t_lex *lex, t_child **child, t_exec *exec)
{
	lex->iter = 0;
	while (child[lex->iter])
	{
		if (check_commands(lex, child, exec) != 0)
			return (1);
		lex->iter++;
	}
	return (0);
	// PRINT COMMAND PATHS
	// int k = 0;
	// while (child[k])
	// {
	// 	printf ("child %d, commandpath: %s\n", k, child[k]->command);
	// 	k++;
	// }
}
