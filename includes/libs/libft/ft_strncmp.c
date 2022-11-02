/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 19:51:05 by amechain          #+#    #+#             */
/*   Updated: 2022/11/02 13:23:28 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			c;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	c = 0;
	if (!str1 && !str2)
		return (0);
	if (!str1 && str2 || str1 && !str2)
		return (1);
	if (n == 0)
		return (0);
	while (str1[c] && str2[c] && str1[c] == str2[c] && n > c + 1)
		c++;
	return (str1[c] - str2[c]);
}
