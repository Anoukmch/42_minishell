/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:40:08 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/14 19:56:39 by amechain         ###   ########.fr       */
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
