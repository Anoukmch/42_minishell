/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 13:01:02 by amechain          #+#    #+#             */
/*   Updated: 2022/04/21 12:00:42 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dstchar;
	char	*srcchar;

	dstchar = (char *)dst;
	srcchar = (char *)src;
	i = 0;
	if (dstchar == NULL && srcchar == NULL)
		return (NULL);
	while (i < n)
	{
		dstchar[i] = srcchar[i];
		i++;
	}
	return ((void *)dst);
}
