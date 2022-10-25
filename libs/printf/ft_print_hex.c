/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:50:59 by amechain          #+#    #+#             */
/*   Updated: 2022/05/12 14:01:44 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*hex_to_str(unsigned int usn, int c, int num)
{
	char			*str;
	unsigned int	tmp;

	str = malloc((num + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[num] = '\0';
	if (usn == 0)
	{
		*str = '0';
		return (str);
	}
	while (usn)
	{
		num--;
		tmp = usn % 16;
		if (tmp < 10)
			tmp = tmp + '0';
		else
			tmp = tmp - 10 + c;
		str[num] = tmp;
		usn = usn / 16;
	}
	return (str);
}

int	output_hex(unsigned int usn, int c)
{
	int				num;
	unsigned int	tmp;
	char			*str;

	num = 0;
	tmp = usn;
	if (usn == 0)
		num++;
	while (usn)
	{
		usn /= 16;
		num++;
	}
	usn = tmp;
	str = hex_to_str(usn, c, num);
	output_string(str);
	free(str);
	return (num);
}
