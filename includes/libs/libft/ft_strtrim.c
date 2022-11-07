/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 11:38:20 by amechain          #+#    #+#             */
/*   Updated: 2022/11/07 16:25:00 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_end(char *str, char *set2)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(str);
	while (i < size)
	{
		if (ft_strchr(set2, str[size - i - 1]) == 0)
			break ;
		i++;
	}
	return (size - i);
}

static int	ft_beg(char *str, char *set2)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(str);
	while (i < size)
	{
		if (ft_strchr(set2, str[i]) == 0)
			break ;
		i++;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	char	*set2;
	char	*new;
	int		beg;
	int		end;

	if (s1 == NULL || set == NULL)
		return (NULL);
	str = (char *)s1;
	set2 = (char *)set;
	beg = ft_beg(str, set2);
	end = ft_end(str, set2);
	if (beg >= end)
		new = (char *)malloc(sizeof(char));
	else
		new = (char *)malloc(sizeof(char) * (end - beg + 1));
	if (new == NULL)
		return (NULL);
	ft_strlcpy(new, str + beg, end - beg + 1);
	return (new);
}

