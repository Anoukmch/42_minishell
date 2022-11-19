#include "../../includes/minishell.h"

int	get_env_path(t_env *env)
{
	int		i;
	char	**tmp;
	int		size;

	i = 0;
	tmp = ft_split(env->envp_line, ':');
	free (env->envp_line);
	if (!tmp)
		return (1);
	size = doublepoint_size (tmp);
	env->envp_path = ft_calloc(size + 1, sizeof(char *));
	if (!env->envp_path)
		return (1);
	while (tmp[i])
	{
		env->envp_path[i] = ft_strjoin(tmp[i], "/");
		if (!env->envp_path[i])
			return (1);
		i++;
	}
	free_array(tmp);
	return (0);
}

int	get_path_from_env(t_env *env, t_child *child)
{
	int	i;

	i = 0;
	if (!env->envp_bis && !child->command
		&& !ft_strchr(child->parser_cmd[0], '/'))
		return (perror_return_status("command not found", 0));
	while (env->envp_bis[i])
	{
		if (!ft_strncmp(env->envp_bis[i], "PATH", 4))
		{
			env->envp_line
				= ft_strdup(env->envp_bis[i] + 5); //PATH FROM OWN ENVIRONMENT
			if (!env->envp_line)
				return (perror_return_status("command not found", 0)); //path of command not found environment disabled
				//path of command not found -> path unset
			break ;
		}
		i++;
	}
	if (get_env_path(env))
		return (1);
	return (0);
}
