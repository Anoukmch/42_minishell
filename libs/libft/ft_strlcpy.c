/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:50:54 by amechain          #+#    #+#             */
/*   Updated: 2022/04/21 15:34:08 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	char	*srcchar;
	size_t	s;
	size_t	c;

	srcchar = (char *)src;
	c = 0;
	s = ft_strlen(srcchar);
	if (dstsize != 0)
	{
		while (c < dstsize - 1 && srcchar[c] != '\0')
		{
			dst[c] = srcchar[c];
			c++;
		}
		dst[c] = '\0';
	}
	return (s);
}
