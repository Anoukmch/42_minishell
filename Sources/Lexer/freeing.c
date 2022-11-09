/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:40:08 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/09 13:12:07 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_doublepointer(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free (str[i]);
		i++;
	}
	free (str);
}

void	errorexit(char *message)
{
	ft_putstr_fd(message, 2);
	exit(EXIT_FAILURE);
}
