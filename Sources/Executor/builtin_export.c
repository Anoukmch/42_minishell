
#include "../../includes/minishell.h"

static int	invalid_identifier(char *cmd)
{
	int	i;

	i = 0;
	if ((!ft_isalpha(cmd[0]) && cmd[0] != '_'))
	{
		g_exit_code = 1;
		return (perror_return_status("export: not a valid identifier\n", 0));
	}
	while (cmd[i] && cmd[i] != '=')
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
		{
			g_exit_code = 1;
			return (perror_return_status("export: not a valid identifier\n", 0));
		}
		i++;
	}
	return (0);
}

int	replace_variable(t_env *env, char *variable, char *content)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strjoin(variable, "=");
	if (!tmp)
		return (1);
	while (env->envp_bis[i])
	{
		if (!ft_strncmp(env->envp_bis[i], variable, ft_strlen(variable)))
		{
			free (env->envp_bis[i]);
			if (content)
				env->envp_bis[i] = ft_strjoin(tmp, content);
			else
				env->envp_bis[i] = ft_strdup(variable);
			free (tmp);
			if (!env->envp_bis[i])
				return (1);
			return (2);
		}
		i++;
	}
	free (tmp);
	return (0);
}

char	**add_variable_export(t_env *env, char *variablename)
{
	char	**new;
	char	*tmp;
	int		size;
	int		i;

	new = NULL;
	tmp = NULL;
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
	new[size++] = ft_strdup(variablename);
	if (!new[size - 1])
		return (NULL);
	new[size] = NULL;
	free_array(env->envp_bis);
	return (new);
}

void freeing_variables_env(char *variablename, char *content, t_env *env)
{
	free_array(env->envp_bis);
	free (content);
	free (variablename);
}

char	**add_variable_env(t_env *env, char *variablename, char *content)
{
	char	**new;
	char	*tmp;
	int		size;
	int		i;

	new = NULL;
	tmp = NULL;
	size = doublepoint_size(env->envp_bis);
	new = ft_calloc(size + 2, sizeof(char *));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (env->envp_bis[i])
	{
		new[i] = ft_strdup(env->envp_bis[i]);
		if (!new[i])
			return (NULL);
		i++;
	}
	tmp = ft_strjoin(variablename, "=");
	if (!tmp)
		return (NULL);
	new[size++] = ft_strjoin(tmp, content);
	free (tmp);
	if (!new[size - 1])
		return (NULL);
	new[size] = NULL;
	freeing_variables_env(variablename, content, env);
	return (new);
}

int	export_variable(char *str, t_env *env)
{
	char	*variable;
	int		i;
	int		replace;

	i = 0;
	variable = NULL;
	variable = str;
	replace = replace_variable(env, variable, NULL);
	if (replace == 1)
		return (1);
	if (!replace)
	{
		env->envp_bis = add_variable_export(env, variable);
		if (!env->envp_bis)
			return (1);
	}
	return (0);
}

int	env_variable(char *str, t_env *env)
{
	char	*variablename;
	char	*content;
	int		replace;

	variablename = NULL;
	content = NULL;
	variablename = ft_substr(str, 0,
			ft_strlen(str) - ft_strlen(ft_strchr(str, '=')));
	content = ft_substr(str, ft_strlen(variablename) + 1,
			ft_strlen(ft_strchr(str, '=')) + 1);
	if (ft_strlen(content) == 0)
		content = ft_strdup("");
	if (!content || !variablename)
		return (1);
	replace = replace_variable(env, variablename, content);
	if (replace == 1)
		return (1);
	if (!replace)
	{
		env->envp_bis = add_variable_env(env, variablename, content);
		if (!env->envp_bis)
			return (1);
	}
	return (0);
}

int	command_export(t_child *child, t_env *env)
{
	int	i;

	i = 1;
	if (child->parser_cmd[i] == NULL)
	{
		if (no_options(env))
			return (1);
		return (0);
	}
	while (child->parser_cmd[i])
	{
		if (!invalid_identifier(child->parser_cmd[i]))
		{
			if (ft_strchr(child->parser_cmd[i], '=')
				&& env_variable(child->parser_cmd[i], env))
				return (1);
			else if (!ft_strchr(child->parser_cmd[i], '=')
				&& export_variable(child->parser_cmd[i], env))
				return (1);
		}
		i++;
	}
	return (0);
}
