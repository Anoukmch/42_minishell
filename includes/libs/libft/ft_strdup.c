/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 15:22:18 by amechain          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/11/14 14:58:42 by amechain         ###   ########.fr       */
=======
/*   Updated: 2022/11/14 16:33:31 by jmatheis         ###   ########.fr       */
>>>>>>> 1ab993aeff9f117e20ed125bd8850b2541516140
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*dst;
	char	*str;

	i = 0;
	dst = NULL;
	str = (char *)s1;
	while (s1[i])
		i++;
	dst = (char *)malloc(sizeof(char) * (i + 1));
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
