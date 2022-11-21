#include "../../../includes/minishell.h"

int	replace_variable(t_env *env, char *variable, char *content)
{
	char	*tmp;

	tmp = ft_strjoin(variable, "=");
	if (!tmp)
		return (1);
	while (env->envp_bis[env->env_i])
	{
		if (!ft_strncmp(env->envp_bis[env->env_i],
				variable, ft_strlen(variable) + 1)
			|| !ft_strncmp(env->envp_bis[env->env_i], tmp, ft_strlen(tmp)))
		{
			free (env->envp_bis[env->env_i]);
			if (content)
				env->envp_bis[env->env_i] = ft_strjoin(tmp, content);
			else
				env->envp_bis[env->env_i] = ft_strdup(variable);
			free (tmp);
			if (!env->envp_bis[env->env_i])
				return (1);
			return (2);
		}
		env->env_i++;
	}
	free (tmp);
	return (0);
}

int	add_new_variable(char **new, int *size, char *variablename, char *content)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strjoin(variablename, "=");
	if (!tmp)
		return (1);
	if (content)
		new[(*size)++] = ft_strjoin(tmp, content);
	else
		new[(*size)++] = ft_strdup(variablename);
	free (tmp);
	if (!new[(*size) - 1])
		return (1);
	new[(*size)] = NULL;
	return (0);
}

char	**create_new_env(t_env *env, char *variablename, char *content)
{
	char	**new;
	int		size;
	int		i;

	new = NULL;
	size = doublepoint_size(env->envp_bis);
	new = ft_calloc(size + 2, sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (env->envp_bis[i])
	{
		new[i] = ft_strdup(env->envp_bis[i]);
		if (!new[i])
			return (NULL);
		i++;
	}
	if (add_new_variable(new, &size, variablename, content))
		return (NULL);
	free_array(env->envp_bis);
	return (new);
}

char	*add_quotes(char *adding)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = NULL;
	tmp = ft_calloc(ft_strlen(adding) + 3, sizeof(char));
	if (!tmp)
		return (NULL);
	while (adding[i] != '\0')
	{
		if (adding[j] == '=')
		{
			tmp[j++] = adding[i];
			tmp[j] = '"';
		}
		else
			tmp[j] = adding[i];
		j++;
		i++;
	}
	tmp[j++] = '\"';
	tmp[j] = '\0';
	return (tmp);
}

int	no_options(t_env *env)
{
	int		i;
	char	**export;

	i = 0;
	export = NULL;
	while (env->envp_bis[i])
		i++;
	export = ft_calloc(i + 1, sizeof(char *));
	if (export == NULL)
		return (1);
	i = 0;
	while (env->envp_bis[i])
	{
		if (ft_strchr(env->envp_bis[i], '=') != NULL)
			export[i] = add_quotes(env->envp_bis[i]);
		else
			export[i] = ft_strdup(env->envp_bis[i]);
		if (!export[i])
			return (1);
		ft_printf("declare -x ");
		ft_printf("%s\n", export[i]);
		i++;
	}
	free_array(export);
	return (0);
}
