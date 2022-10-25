/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:51:02 by amechain          #+#    #+#             */
/*   Updated: 2022/05/12 14:14:50 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	ft_itoa_size_bis(unsigned int n)
{
	int	size;

	size = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

static char	*ft_itoa_bis(unsigned int n)
{
	char	*str;
	int		i;
	int		size;

	size = ft_itoa_size_bis(n);
	i = 1;
	str = (char *)malloc(sizeof(char) * size + 1);
	if (str == NULL)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	while (n >= 1)
	{
		str[size - i++] = (n % 10) + '0';
		n /= 10;
	}
	str[size] = '\0';
	return (str);
}

int	output_integer(int c)
{
	char	*str;
	int		i;

	str = ft_itoa(c);
	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	free(str);
	return (i);
}

int	output_unsigned_decimal(unsigned int c)
{
	char	*str;
	int		i;

	str = ft_itoa_bis(c);
	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	free(str);
	return (i);
}
