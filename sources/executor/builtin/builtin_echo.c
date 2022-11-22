/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:22:05 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/22 15:22:06 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	command_echo_bis(t_child *child, int *i)
{
	if (!ft_strcmp(child->parser_cmd[1], "~"))
		ft_printf("%s", getenv("HOME"));
	else
		ft_printf("%s", child->parser_cmd[*i]);
	if (child->parser_cmd[*i + 1] != NULL)
		ft_printf(" ");
	(*i)++;
}

int	command_echo(t_child *child)
{
	int		i;
	int		j;
	bool	newline;

	i = 1;
	newline = true;
	j = 1;
	while (child->parser_cmd[i] != NULL && child->parser_cmd[i][0] == '-'
		&& ft_strlen(child->parser_cmd[i]) > 1)
	{
		while (child->parser_cmd[i][j] == 'n')
			j++;
		if (child->parser_cmd[i][j] != '\0')
			break ;
		else
			newline = false;
		i++;
	}
	while (child->parser_cmd[i])
		command_echo_bis(child, &i);
	if (newline == true)
		ft_printf("\n");
	return (0);
}
