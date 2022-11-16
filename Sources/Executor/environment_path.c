#include "../../includes/minishell.h"

int	get_env_path(t_env *env)
{
	int	i;

	i = 0;
	env->envp_path = ft_split(env->envp_line, ':');
	if (!env->envp_path)
		return (1);
	while (env->envp_path[i])
	{
		free (env->envp_path[i]);
		env->envp_path[i] = ft_strjoin(env->envp_path[i], "/");
		if (!env->envp_path[i])
			return (1);
		i++;
	}
	return (0);
}

int	get_path_from_env(t_env *env, t_child *child)
{
	int	i;

	i = 0;
	if (!env->envp_bis && !child->command && !ft_strchr(child->parser_cmd[0], '/'))
	{
		perror_return_status("command not found", 127);
		return (0); //path of command not found environment disabled
	}
	while (env->envp_bis[i])
	{
		if (!ft_strncmp(env->envp_bis[i], "PATH", 4))
		{
			env->envp_line = ft_strchr(env->envp_bis[i], '/'); //PATH FROM OWN ENVIRONMENT
			if (!env->envp_line)
			{
				perror_return_status("command not found", 127);
				return (0); //path of command not found environment disabled
			}	 //path of command not found -> path unset
			break ;
		}
		i++;
	}
	if (get_env_path(env))
		return (1);
	return (0);
}