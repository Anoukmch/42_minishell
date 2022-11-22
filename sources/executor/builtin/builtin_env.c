/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:22:10 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/22 15:22:11 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	command_env(t_env *env)
{
	int	i;

	i = 0;
	while (env->envp_bis[i])
	{
		if (ft_strchr(env->envp_bis[i], '='))
			ft_printf("%s\n", env->envp_bis[i]);
		i++;
	}
	return (0);
}
