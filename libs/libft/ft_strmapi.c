/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:01:15 by amechain          #+#    #+#             */
/*   Updated: 2022/04/21 12:01:25 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char				*str;
	unsigned int		i;
	int					len;
	char				*new;

	if (s == NULL)
		return (NULL);
	new = NULL;
	str = (char *)s;
	len = ft_strlen(str);
	i = 0;
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (0);
	while (str[i])
	{
		new[i] = f(i, str[i]);
		i++;
	}
	new[i] = '\0';
	return (new);
}
