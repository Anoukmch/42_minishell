/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 10:42:35 by amechain          #+#    #+#             */
/*   Updated: 2022/04/26 16:28:15 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	char	*substring;
	size_t	i;

	str = (char *)s;
	substring = NULL;
	i = 0;
	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	if (start >= ft_strlen(s))
		len = 0;
	substring = (char *)malloc(sizeof(char) * len + 1);
	if (substring == NULL)
		return (0);
	while (i < len && str[start] && start < ft_strlen(str))
	{
		substring[i] = str[start];
		start++;
		i++;
	}
	substring[i] = '\0';
	return (substring);
}
