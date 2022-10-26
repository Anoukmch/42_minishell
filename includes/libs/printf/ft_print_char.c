/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:49:25 by amechain          #+#    #+#             */
/*   Updated: 2022/05/11 14:48:23 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	output_char(char c)
{
	write(1, &c, 1);
	return (1);
}

int	output_string(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (ft_printf("(null)"));
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}
