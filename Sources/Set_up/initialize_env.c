#include "../../includes/minishell.h"

int	doublepoint_size(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

static char	**init_environment(char **envp, t_env *env)
{
	int	size;
	int	i;

	size = doublepoint_size(envp);
	i = 0;
	if (envp[0] == NULL)
	{
		env->envp_bis = ft_calloc(3 + 1, sizeof(char *));
		if (env->envp_bis == NULL)
			return (NULL);
		env->envp_bis[0] = ft_strjoin("PWD=", getcwd(NULL, 0));
		env->envp_bis[1] = ft_strdup("SHLVL=1");
		env->envp_bis[2] = ft_strdup("_=/usr/bin/env");
		env->envp_bis[3] = NULL;
	}
	else
	{
		env->envp_bis = ft_calloc(size + 1, sizeof(char *));
		if (env->envp_bis == NULL)
			return (NULL);
		while (envp[i])
		{
			env->envp_bis[i] = ft_strdup(envp[i]);
			if (!env->envp_bis[i])
				return (NULL);
			i++;
		}
		env->envp_bis[i] = NULL;
	}
	return (env->envp_bis);
}

t_env	*initialize_env(char **envp)
{
	t_env	*env;

	env = ft_calloc(1, sizeof(t_env));
	if (env == NULL)
		return (NULL);
	env->envp_line = NULL;
	env->envp_path = NULL;
	env->envp_bis = init_environment(envp, env);
	if (!env->envp_bis)
		return (NULL);
	return (env);
}
