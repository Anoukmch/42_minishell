/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_and_unset.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:56:46 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/07 18:05:14 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	export environment variables
	create new ones & replace old ones
	check them with env
	use unset to remove some of them
	check the result with env
*/
// static int	no_equalsign(char **cmd)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while(cmd[j])
// 	{
// 		while(cmd[j][i])
// 		{
// 			if (cmd[j][i] == '=')
// 				return (0);
// 			i++;
// 		}
// 		i = 0;
// 		j++;
// 	}
// 	return (1);
// }

static char	*delete_quotes(char *str)
{
	if (ft_strtrim(str, "\"") != NULL)
		str = ft_strtrim(str, "\"");
	if (ft_strtrim(str, "'") != NULL)
		str = ft_strtrim(str, "'");
	return (str);
}

// NOT WORKING:
	// export ''=''
	// export ""=""
	// 
/*
	bool = 1 --> single quotes
	bool = 2 --> double quotes
	"\"" --> string with one double quote
*/
static int	invalid_identifier(char **cmd)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (cmd && cmd[i])
	{
		cmd[i] = delete_quotes(cmd[i]);
		while (cmd[i][j] != '\0')
		{	
			if (cmd[i][0] == '=')
				printf("WORKS HERE\n");
			if (ft_isdigit(cmd[i][0]) != 0 || cmd[i][0] == '='
				|| ((ft_isalnum(cmd[i][j]) == 0) && cmd[i][j] != '_'
					&& cmd[i][j] != '=' && cmd[i][j] != 39 && cmd[i][j] != '"'))
			{
				printf("export: '%s': not a valid identifier\n", cmd[i]);
				return (1);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

static void	export_variable(char *str)
{
	printf("EXPORT\n");
	char	*variable;

	variable = NULL;
	variable = str;
	// ADD IT TO EXPORT
	printf("variable: %s\n", variable);
}

static void	env_variable(char *str)
{
	char	*variablename;
	char	*content;

	printf("ENV\n");
	variablename = NULL;
	content = NULL;
	variablename = ft_substr(str, 0,
			ft_strlen(str) - ft_strlen(ft_strchr(str, '=')));
	content = ft_substr(str, ft_strlen(variablename) + 1,
			ft_strlen(ft_strchr(str, '=')) + 1);
	content = delete_quotes(content);
	if (ft_strlen(content) == 0)
		content = "";
	// ADD IT TO ENV
	printf("variablename: %s\n", variablename);
	printf("content: %s\n", content);
}

//cmd[0] = "export";
// IMPORTANT: Last string = NULL
void	command_export(char **cmd)
{
	int	i;

	i = 1;
	if (cmd[i] == NULL)
	{
		printf("declare -x\n");
		//print whole env with declare -x in front
		return ;
	}
	if (invalid_identifier(cmd) != 0)
	{
		printf("error occured\n");
		return ;
	}
	while (cmd[i] && cmd)
	{
		if (ft_strchr(cmd[i], '=') != NULL)
			env_variable(cmd[i]);
		else
			export_variable(cmd[i]);
		i++;
	}
}

/*
	export: `=============123': not a valid identifier
	export: `=': not a valid identifier
	export: `=42': not a valid identifier
	export: `?=hallo': not a valid identifier
	export test =1 --> export: `=1': not a valid identifier
	export test ? --> export: `?': not a valid identifier
	export ''=''
	export ""=""
	--> INFRONT OF = MUST BE A ALPHABETICAL CHARACTER, otherwise: not a valid identifier
	--> only letters & _, numbers after a letter is fine
	export export //nothing happens
	export echo //nothing happens
	export cd //nothing happens
	export test //nothing happens
	export TEST //nothing happens
	export
	--> if after EXPORT sth without = --> NOTHING HAPPENS

	//WORKS:
	export TES_T=123 --> echo TES_T --> 123, in env: TES_T=123
	export HELLO42=T="" -->echo HELLO42 --> T=, in env: HELLO42=T=
	export mini_test= --> echo $mini_test --> empty line, in env: mini_test=
	export test= test --> echo $test --> empty line, in env: test=
	export test test=  --> echo $test --> empty line, in env: test=
	export test= test= --> echo $test --> empty line, in env: test=
	if echo $random (variable is not exported) --> return empty line

	export test=42 | echo 99 --> first process gets ignored, only second one is executed
*/