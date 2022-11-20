#include "../../includes/minishell.h"

int	get_position_of_variable(t_env *env, char *variable)
{
	int	i;

	i = 0;
	while (env->envp_bis[i])
	{
		if (ft_strncmp(env->envp_bis[i], variable, ft_strlen(variable)) == 0)
			return (i);
		i++;
	}
	return (-1);
}
