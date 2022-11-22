/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_handler_utils_hd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:25:28 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/22 15:25:29 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	nbr_dollar_sign_hd(char *lex_string)
{
	int	size;
	int	count;

	count = 0;
	size = ft_strlen(lex_string) - 1;
	while (size >= 0)
	{
		if (lex_string[size] == '$')
			count++;
		size--;
	}
	return (count);
}
