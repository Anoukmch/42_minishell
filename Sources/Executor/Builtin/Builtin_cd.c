#include "../../../includes/minishell.h"

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

int	update_pwd(t_env *env)
{
	int		oldpwd;
	int		pwd;

	oldpwd = get_position_of_variable(env, "OLDPWD");
	pwd = get_position_of_variable(env, "PWD");
	if (pwd >= 0)
	{
		if (oldpwd >= 0)
		{
			free(env->envp_bis[oldpwd]);
			env->envp_bis[oldpwd]
				= ft_strjoin("OLDPWD", ft_strchr(env->envp_bis[pwd], '='));
			if (!env->envp_bis[oldpwd])
				return (1);
		}
		free(env->envp_bis[pwd]);
		env->envp_bis[pwd] = ft_strjoin("PWD=", getcwd(NULL, 0));
		if (!env->envp_bis[pwd])
			return (1);
	}
	return (0);
}

int	command_cd(t_child *child, t_env *env)
{
	if (child->parser_cmd[1] == NULL || !ft_strcmp(child->parser_cmd[1], "~"))
	{
		if (chdir(getenv("HOME")) != 0)
			return (perror_return_status(NULL, 1));
	}
	else
	{
		if (child->parser_cmd[1][0] != '\0' && chdir(child->parser_cmd[1]) != 0)
			return (perror_return_status(NULL, 1));
	}
	if (update_pwd(env))
		return (1);
	return (0);
}
