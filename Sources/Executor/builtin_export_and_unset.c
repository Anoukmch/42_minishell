/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_and_unset.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:56:46 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/04 15:22:58 by jmatheis         ###   ########.fr       */
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
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
	{
		return (1);
	}
	return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) == 1 || ft_isdigit(c) == 1)
		return (1);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	c;
	char	*str;

	c = 0;
	str = (char *)s;
	while (str[c])
		c++;
	return (c);
}

int	unvalid_identifier(char **cmd)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (cmd && cmd[i])
	{
		// DELETE QUOTES IF THEY ARE CLOSED BEFORE WHILE LOOP
		while (cmd[i][j])
		{
			printf("CHAR: %c\n", cmd[i][j]);
			if (ft_isdigit(cmd[i][0]) != 0 || cmd[i][0] == '='
				|| (ft_isalnum(cmd[i][j]) == 0) && cmd[i][j] != '_'
					&& cmd[i][j] != '=' && cmd[i][j] != 39 && cmd[i][j] != '"')
			{
				printf("export: '%s': not a valid identifier\n", cmd[i]);
				return (1);
			}
			if (cmd[i][j] == '=')
				break ;
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

//cmd[0] = "export";
// IMPORTANT: Last string = NULL
void	command_export (char **cmd)
{
	int	i;

	i = 0;
	if (cmd[1] == NULL)
	{
		printf("declare -x\n"); //print whole env with declare -x in front
		return ;
	}
	// delete quotes
	if (unvalid_identifier(cmd) != 0)
		return ;
	// while (cmd[i] && cmd)
	// {
	// 	if (ft_strchr(cmd[i], '=') == NULL)
	// 	i++
	// }
	
	
}

int main (void)
{
	char **test;
	test[0] = "export";
	test[1] = "export";
	// test[2] = "te";
	test[2] = NULL;
	command_export(test);
	return(0);
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