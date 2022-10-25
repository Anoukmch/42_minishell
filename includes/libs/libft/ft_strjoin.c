/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 11:08:10 by amechain          #+#    #+#             */
/*   Updated: 2022/04/21 09:47:43 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	new = (char *)malloc(sizeof(char) * (ft_strlen((char *)s1)
				+ ft_strlen((char *)s2) + 1));
	if (new == NULL)
		return (NULL);
	while ((char)s1[i])
	{
		new[i] = (char)s1[i];
		i++;
	}
	while ((char)s2[j])
	{
		new[i] = (char)s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}
