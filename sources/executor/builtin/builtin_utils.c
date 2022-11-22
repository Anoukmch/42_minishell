/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:22:43 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/22 15:22:44 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_only_digits(char *str)
{
	int	i;

	i = 0;
	if ((str[i] == '-' && str[i + 1])
		|| (str[i] == '+' && str[i + 1]))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

bool	ft_atoilong(long long int *buffer, char *s)
{
	unsigned long long	res;
	int					sign;
	int					c;

	c = 0;
	sign = 1;
	res = 0;
	while ((s[c] >= '\t' && s[c] <= '\r') || (s[c] == ' '))
		c++;
	if (s[c] == '-')
	{
		sign = -1;
		c++;
	}
	else if (s[c] == '+')
		c++;
	while (s[c] >= '0' && s[c] <= '9')
		res = (res * 10) + (s[c++] - '0');
	if ((res == ((unsigned long long)LLONG_MAX + 1) && sign == 1)
		|| res > ((unsigned long long)LLONG_MAX + 1))
		return (true);
	*buffer = (long long int)res * sign;
	return (false);
}
