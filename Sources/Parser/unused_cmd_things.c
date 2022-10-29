/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:18:25 by jmatheis          #+#    #+#             */
/*   Updated: 2022/10/26 17:53:40 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static void	parse_builtin_cmds(t_lex *lex, t_child *child, int i, int j)
// {
// 	if(ft_strncmp("echo", lex->lexer[i], 5) == 0)
// 	{
// 		if(ft_strncmp("-n", lex->lexer[i], 3) == 0)
// 		{
// 			child->parser_cmd = ft_calloc(2, 2 * sizeof(char *));
// 			if(child->parser_cmd == NULL)
// 			{
// 				printf("Parser_cmd is NULL");
// 				exit (1);
// 			}
// 			child->parser_cmd[j++] = lex->lexer[i++];
// 		}
// 		else
// 		{
// 			child->parser_cmd = ft_calloc(1, 1 * sizeof(char *));
// 			if(child->parser_cmd == NULL)
// 			{
// 				printf("Parser_cmd is NULL");
// 				exit (1);
// 			}	
// 			child->parser_cmd[j++] = lex->lexer[i];	
// 		}
// 		exit (0);
// 	}
// 	if(ft_strncmp("cd", lex->lexer[i], 3) == 0)
// 		child->parser_cmd[j++] = lex->lexer[i];
// 	if(ft_strncmp("pwd", lex->lexer[i], 4) == 0)
// 		child->parser_cmd[j++] = lex->lexer[i];
// 	if(ft_strncmp("export", lex->lexer[i], 7) == 0)
// 		child->parser_cmd[j++] = lex->lexer[i];
// 	if(ft_strncmp("unset", lex->lexer[i], 6) == 0)
// 		child->parser_cmd[j++] = lex->lexer[i];
// 	if(ft_strncmp("env", lex->lexer[i], 4) == 0)
// 		child->parser_cmd[j++] = lex->lexer[i];
// 	if(ft_strncmp("exit", lex->lexer[i], 5) == 0)
// 		child->parser_cmd[j++] = lex->lexer[i];
// }

// static void parse_env_cmds(t_lex *lex, t_child *child, int i, int j)
// {
// 	char *env_path;
// 	char **env_dirs;
// 	int	z;

// 	env_path = NULL;
// 	env_dirs = NULL;
// 	z = 0;
// 	env_path = getenv("PATH");
// 	env_path = ft_strchr(env_path, '/');
// 	env_dirs = ft_split(env_path, ':');
// 	if (env_path == NULL || env_dirs == NULL || ft_strchr(lex->lexer[i], '/') != NULL)
// 	{
// 		if (access(lex->lexer[i], 0) == 0)
// 			child->parser_cmd[j++] = lex->lexer[i];
// 		// CHECK FOR COMMAND ARGUMENT --> strjoin
// 		// Check until next thing is not an argument of cmd
// 	}
// 	while (env_dirs && env_dirs[z])
// 	{
// 		if(access(ft_strjoin(env_dirs[z], lex->lexer[i]), 0) == 0)
// 		{
// 			child->parser_cmd = ft_calloc(1, 1 * sizeof(char *));
// 			if (child->parser_cmd == NULL)
// 			{
// 				printf("Parser_cmd IS NULL");
// 				exit(1);
// 			}
// 			child->parser_cmd[j++] = lex->lexer[i];
// 		}
// 		// CHECK FOR COMMAND ARGUMENT -->strjoin
// 		// Check until next thing is not an argument of cmd
// 		z++;
// 	}
// 	z = 0;
// 	while(env_dirs && env_dirs[z])
// 	{
// 		free(env_dirs[z]);
// 		z++;
// 	}
// 	free(env_dirs);	
// }

static void	commands_with_arguments(t_lex *lex, int i, t_child **child, int	k)
{
	int	z;

	z = 0;
	printf("CMD");
	while(ft_strncmp(lex->lexer[i],"<", 2) != 0 && ft_strncmp(lex->lexer[i],"<<", 3) != 0
			&& ft_strncmp(lex->lexer[i],">", 2) != 0 && ft_strncmp(lex->lexer[i],">>", 3) != 0
			&& ft_strncmp(lex->lexer[i],"|", 2) != 0)
	{
		// ALLOCATE PARSER_CMD
		child[k]->parser_cmd[z] = lex->lexer[i];
		printf("%s\n", child[k]->parser_cmd[z]);
		z++;
		i++;
	}
	exit(0);
}

void	parse_commands(t_lex *lex, t_child **child)
{
	int	i;
	int j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	// if (child == NULL)
	// {
	// 	printf("WORKS\n");
	// }
	while (k <= lex->noofpipes + 2)
	{
		while (ft_strncmp(lex->lexer[i], "|", 2) != 0 && lex->lexer[i])
		{
			printf("CMD");
			while(ft_strncmp(lex->lexer[i],"<", 2) == 0 || ft_strncmp(lex->lexer[i],"<<", 3) == 0
				|| ft_strncmp(lex->lexer[i],">", 2) == 0 || ft_strncmp(lex->lexer[i],">>", 3) == 0)
				i += 2; //THINK ABOUT DOUBLE QUOTES WITH SPACES IN IT IN LEXER IN LEXER
			commands_with_arguments(lex, i, child, k);
			// parse_builtin_cmds(lex, child[k], i, j);
			// parse_env_cmds(lex, child[k], i, j);
			i++;
		}
		j = 0;
		i++;
		k++;
	}
	k = 0;
	j = 0;
	while(child && k <= lex->noofpipes + 2)
	{
		while((*child)->parser_cmd[j])
		{
			printf("WORKS\n");
			printf("child %d: %s\n", k, (*child)->parser_cmd[j]);
			j++;
		}
		j = 0;
		(*child)++;
		k++;
	}
}

// static void env_commands()
// {
//  	char *path;
//     char **folders;
// 	char *cmdpath;
//     int i;

// 	i = 0;
// 	path = getenv("PATH");
// 	path = ft_strchr(path, '/');
// 	if (path == NULL)
//         errorexit("Path not found\n");
//     while(folders[i])
//     {
//     	folders = ft_split(path, ':');
// 		i++;
// 	}
// 	i = 0;
// 	while (folders[i])
// 	{
// 		cmdpath = (ft_strjoin(folders[i], "LEXERTHING"));
// 		if (access(cmdpath, 0) == 0)
// 		{
// 			// CHECK ARGUMENTS OF COMMANDS
// 		}
// 		free (cmdpath);
// 		i++;
// 	}
	// i = 0;
    // while(folders[i])
    // {
	//     printf("%s\n", folders[i]);
    //     i++;
    // }
	// check with env Path
// }

// static void builtins_commands()
// {
// 	// check built-ins with strncmp function
// }

// char	*get_cmdpath(t_var *var, char *cmd)
// {
// 	int		i;
// 	char	*cmdpath;

// 	cmdpath = NULL;
// 	i = 0;
// 	while (var->folders[i])
// 	{
// 		cmdpath = (ft_strjoin(var->folders[i], cmd));
// 		if (access(cmdpath, 0) == 0)
// 			return (cmdpath);
// 		free (cmdpath);
// 		i++;
// 	}
// 	ft_printf("Check commands!\n");
// 	exit(EXIT_FAILURE);
// }