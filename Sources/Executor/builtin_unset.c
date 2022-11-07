/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:44:38 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/07 19:08:59 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*delete_quotes(char *str)
{
	if (ft_strtrim(str, "\"") != NULL)
		str = ft_strtrim(str, "\"");
	if (ft_strtrim(str, "'") != NULL)
		str = ft_strtrim(str, "'");
	return (str);
}

static int	invalid_identifier(char **cmd)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (cmd && cmd[i])
	{
		cmd[i] = delete_quotes(cmd[i]);
		if (cmd[i][0] == '\0')
			printf("unset: '%s': not a valid identifier\n", cmd[i]);
		while (cmd[i][j] != '\0')
		{	
			if (ft_isdigit(cmd[i][0]) != 0 || cmd[i][0] == '='
				|| (ft_isalnum(cmd[i][j]) == 0 && cmd[i][j] != '_'
					&& cmd[i][j] != '=' && cmd[i][j] != 39 && cmd[i][j] != '"'))
			{
				printf("unset: '%s': not a valid identifier\n", cmd[i]);
				return (1);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

void	command_unset(char **cmd)
{
	int	i;

	i = 1;

	if (cmd[i] == NULL)
	{
		// nothing should happen in this case
		return ;
	}
	if (invalid_identifier(cmd) != 0)
	{
		printf("error occured\n");
		return ;
	}
	// while (cmd[i] && cmd)
	// {
	// 	if VARIABLE EXISTS --> EXECUTE IT
	// 	else
	// 		IF VARIABLE DOESN'T EXIST --> RETUNR NEW LINE
	// 	i++;
	// }
}

/*
	->not a valid identifier
	unset "" X --> IS NOT WORKING
	unset =
	unset "="
	unset ""=
	unset =""
	unset ==
	unset ?
	unset "?"
	unset $
	unset "$"
	unset $""
*/

// in cae of $HOME
// --> unset HOME
// --> echo HOME --> new line
// IF VARIABLE DOESN'T EXIST --> RETURN NEW LINE