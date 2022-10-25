/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:21:51 by amechain          #+#    #+#             */
/*   Updated: 2022/04/17 09:14:20 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char	*srcchar;
	size_t	srclen;
	size_t	destlen;
	int		i;

	srcchar = (char *)src;
	i = 0;
	destlen = ft_strlen(dst);
	srclen = ft_strlen(srcchar);
	if (dstsize <= destlen)
		return (dstsize + srclen);
	while (srcchar[i] != '\0' && (destlen + i) < (dstsize - 1))
	{
		dst[destlen + i] = srcchar[i];
		i++;
	}
	dst[destlen + i] = '\0';
	return (destlen + srclen);
}
