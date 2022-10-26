/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:59:04 by jmatheis          #+#    #+#             */
/*   Updated: 2022/10/26 12:53:08 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void redirections(int i, t_lex *lex, t_child *child)
{
	if (lex->lexer[i] = "<")
	// parser_redirect[0]
	if (lex->lexer[i] = ">")
	// parser_redirect[1]
	if (lex->lexer[i] = ">>")
	// parser_redirect[2]
	if (lex->lexer[i] = "<<")
	// parser_redirect[3]
}

static void env_commands()
{
 	char *path;
    char **folders;
	char *cmdpath;
    int i;

	i = 0;
	path = getenv("PATH");
	path = ft_strchr(path, '/');
	if (path == NULL)
        errorexit("Path not found\n");
    while(folders[i])
    {
    	folders = ft_split(path, ':');
		i++;
	}
	i = 0;
	while (folders[i])
	{
		cmdpath = (ft_strjoin(folders[i], "LEXERTHING"));
		if (access(cmdpath, 0) == 0)
		{
			// CHECK ARGUMENTS OF COMMANDS
		}
		free (cmdpath);
		i++;
	}
	// i = 0;
    // while(folders[i])
    // {
	//     printf("%s\n", folders[i]);
    //     i++;
    // }
	// check with env Path
}

static void builtins_commands()
{
	// check built-ins with strncmp function
}

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

void parser(t_lex *lex, t_child **child)
{
	int	i;

	i = 0;
	t_child **child;
	//  IN CASE OF PIPE --> CHANGE PROCESS NUMBER
	while (lex->lexer[i])
	{
		builtins_commands();
		env_commands();
		redirections(i, lex, child);
		i++;
	}
}
