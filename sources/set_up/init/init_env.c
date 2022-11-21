#include "../../../includes/minishell.h"

int	doublepoint_size(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

static char	**init_disabled_env(t_env *env)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	env->envp_bis = ft_calloc(3 + 1, sizeof(char *));
	if (!env->envp_bis)
		return (NULL);
	env->envp_bis[0] = ft_strjoin("PWD=", dir);
	if (!env->envp_bis[0])
		return (NULL);
	free (dir);
	env->envp_bis[1] = ft_strdup("SHLVL=1");
	if (!env->envp_bis[1])
		return (NULL);
	env->envp_bis[2] = ft_strdup("_=/usr/bin/env");
	if (!env->envp_bis[2])
		return (NULL);
	env->envp_bis[3] = NULL;
	return (env->envp_bis);
}

static char	**init_env(char **envp, t_env *env)
{
	int	size;
	int	i;

	size = doublepoint_size(envp);
	i = 0;
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
	if (envp[0] == NULL)
		env->envp_bis = init_disabled_env(env);
	else
		env->envp_bis = init_env(envp, env);
	if (!env->envp_bis)
		return (NULL);
	env->c1 = 0;
	env->c2 = 0;
	env->c3 = 0;
	env->new_arg = NULL;
	env->env_i = 0;
	return (env);
}
