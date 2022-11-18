
#include "../../includes/minishell.h"

/*
	export environment variables
	create new ones & replace old ones
	check them with env
	use unset to remove some of them
	check the result with env
*/

char	*add_quotes(char *adding)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = NULL;
	tmp = ft_calloc(ft_strlen(adding) + 3, sizeof(char));
	if (tmp == NULL)
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
	tmp[j] = '\"';
	j++;
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
			export[i] = ft_strdup(env->envp_bis[i]); /* Check that */
		if (!export[i])
			return (1);
		ft_printf("declare -x ");
		ft_printf("%s\n", export[i]);
		i++;
	}
	free_array(export);
	return (0);
}

static int	invalid_identifier(char *cmd)
{
	int	i;

	i = 0;
	if ((!ft_isalpha(cmd[0]) && cmd[0] != '_'))
	{
		perror_return_status("export: not a valid identifier\n", 1);
		// g_exit_code = 1;
		return (0);
	}
	while (cmd[i] && cmd[i] != '=')
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
			return (perror_return_status("export: not a valid identifier\n", 0));
		i++;
	}
	return (0);
}

char	**add_variable(t_env *env, char *variablename, char *content)
{
	char	**new;
	int		size;
	int		i;

	new = NULL;
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
	if (content == NULL)
	{
		new[size] = ft_strdup(variablename);
		if (!new[size])
			return (NULL);
	}
	else
	{
		new[size] = ft_strjoin(variablename, "=");
		if (!new[size])
			return (NULL);
		free(new[size]);
		new[size] = ft_strjoin(new[size], content);
		if (!new[size])
			return (NULL);
	}
	size++;
	new[size] = NULL;
	free_array(env->envp_bis);
	return (new);
}

// UDPATE VARIABLE
int	export_variable(char *str, t_env *env)
{
	char	*variable;
	int		i;

	i = 0;
	variable = NULL;
	variable = str;
	while (env->envp_bis[i])
	{
		if (ft_strncmp(env->envp_bis[i],
			variable, ft_strlen(variable) + 1) == 0)
		{
			free (env->envp_bis[i]);
			env->envp_bis[i] = ft_strdup(variable);
			if (!env->envp_bis[i])
				return (1);
			return (0);
		}
		i++;
	}
	env->envp_bis = add_variable(env, variable, NULL);
	if (!env->envp_bis)
		return (1);
	return (0);
}

// UPDATE VARIABLE
int	env_variable(char *str, t_env *env)
{
	char	*variablename;
	char	*content;
	int		i;

	i = 0;
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
	while (env->envp_bis[i])
	{
		if (ft_strncmp(env->envp_bis[i], variablename,
				ft_strlen(variablename)) == 0)
		{
			free(env->envp_bis[i]);
			env->envp_bis[i] = ft_strjoin(variablename, "=");
			if (!env->envp_bis[i])
				return (1);
			free(env->envp_bis[i]);
			env->envp_bis[i] = ft_strjoin(env->envp_bis[i], content);
			if (!env->envp_bis[i])
				return (1);
			return (0);
		}
		i++;
	}
	env->envp_bis = add_variable(env, variablename, content);
	if (!env->envp_bis)
		return (1);
	return (0);
}

//cmd[0] = "export";
// IMPORTANT: Last string = NULL
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
			if (ft_strchr(child->parser_cmd[i], '=') != NULL)
			{
				if (env_variable(child->parser_cmd[i], env))
					return (1);
			}
			else
			{
				if (export_variable(child->parser_cmd[i], env))
					return (1);
			}
		}
		i++;
	}
	return (0);
}
