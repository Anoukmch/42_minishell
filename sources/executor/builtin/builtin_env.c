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
