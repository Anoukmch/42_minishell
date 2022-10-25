/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 11:47:09 by amechain          #+#    #+#             */
/*   Updated: 2022/04/21 12:00:49 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*dstchar;
	char	*srcchar;

	dstchar = (char *)dst;
	srcchar = (char *)src;
	i = 0;
	if (dstchar == NULL && srcchar == NULL)
		return (NULL);
	if (dstchar <= srcchar)
	{
		ft_memcpy(dstchar, srcchar, len);
	}
	else if (dstchar > srcchar)
	{
		i = len;
		while (i > 0)
		{
			dstchar[i - 1] = srcchar[i - 1];
			i--;
		}
	}
	return (dst);
}
