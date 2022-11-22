/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:22:27 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/22 15:22:28 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	command_pwd(void)
{
	char	*s;

	s = getcwd(NULL, 0);
	if (!s)
		return (1);
	ft_printf("%s\n", s);
	return (0);
}
