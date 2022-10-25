/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 17:47:49 by amechain          #+#    #+#             */
/*   Updated: 2022/06/22 14:11:33 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_itoa_size(int n)
{
	int				size;

	size = 0;
	if (n < 0 && n > -2147483648)
	{
		size++;
		n = -n;
	}
	else if (n == 0)
		return (1);
	else if (n == -2147483648)
		return (11);
	while (n > 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				i;
	int				size;
	unsigned int	buffer;

	size = ft_itoa_size(n);
	i = 1;
	str = (char *)malloc(sizeof(char) * size + 1);
	if (str == NULL)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	buffer = n;
	if (buffer == 0)
		str[0] = '0';
	while (buffer >= 1)
	{
		str[size - i++] = (buffer % 10) + '0';
		buffer /= 10;
	}
	str[size] = '\0';
	return (str);
}
