/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:26:47 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/22 15:26:48 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strapp(char *s1, char *s2)
{
	char	*temp;

	temp = ft_strjoin(s1, s2);
	if (!temp)
		return (NULL);
	free(s1);
	return (temp);
}
