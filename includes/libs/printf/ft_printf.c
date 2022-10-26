/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 10:49:22 by amechain          #+#    #+#             */
/*   Updated: 2022/05/12 14:10:17 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *s, ...)
{
	va_list	args;
	char	*str;
	int		written;

	str = (char *)s;
	va_start(args, s);
	written = measure_and_output_string(str, args);
	va_end(args);
	return (written);
}

int	check_input(char c, va_list args)
{
	int	nbr;

	nbr = 0;
	if (c == 'c')
		nbr = output_char((char)va_arg(args, int));
	if (c == 's')
		nbr = output_string(va_arg(args, char *));
	if (c == 'p')
		nbr = output_pointer_hex(va_arg(args, unsigned long));
	if (c == 'i' || c == 'd')
		nbr = output_integer(va_arg(args, int));
	if (c == 'u')
		nbr = output_unsigned_decimal(va_arg(args, unsigned int));
	if (c == 'x')
		nbr = output_hex(va_arg(args, unsigned int), 'a');
	if (c == 'X')
		nbr = output_hex(va_arg(args, unsigned int), 'A');
	if (c == '%')
		nbr = output_char('%');
	return (nbr);
}

int	measure_and_output_string(char *str, va_list args)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			len = len + check_input(str[i + 1], args);
			i += 2;
		}
		else
		{
			output_char(str[i]);
			i++;
			len++;
		}
	}
	return (len);
}
