
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
		errorexit("Allocation fail\n");
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

static void	no_options(t_env *env)
{
	int		i;
	char	**export;

	i = 0;
	export = NULL;
	while (env->envp_bis[i])
		i++;
	export = ft_calloc(i + 1, sizeof(char *));
	if (export == NULL)
		errorexit("Allocation error");
	i = 0;
	while (env->envp_bis[i])
	{
		if (ft_strchr(env->envp_bis[i], '=') != NULL)
		{
			export[i] = add_quotes(env->envp_bis[i]);
		}
		else
			export[i] = ft_strdup(env->envp_bis[i]);
		ft_printf("declare -x ");
		ft_printf("%s\n", export[i]);
		i++;
	}
	free_doublepointer(export);
}

static int	invalid_identifier(char **cmd)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (cmd && cmd[i])
	{
		while (cmd[i][j] != '\0')
		{
			if (ft_isdigit(cmd[i][0]) != 0 || cmd[i][0] == '='
				|| (ft_isalnum(cmd[i][j]) == 0 && cmd[i][j] != '_' && cmd[i][j] != ' '
					&& cmd[i][j] != '=' && cmd[i][j] != 39 && cmd[i][j] != '"'))
			{
				ft_putstr_fd("export: '", 2);
				ft_putstr_fd(cmd[i], 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				return (1);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int	doublepoint_size(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}


char **add_variable (t_env *env, char *variablename, char *content)
{
	char **new;
	int	size;
	int	i;

	new = NULL;
	size = doublepoint_size(env->envp_bis);
	new = ft_calloc(size + 2, sizeof(char *));
	if (new  == NULL)
		errorexit("allocation error");
	i = 0;
	while(env->envp_bis[i])
	{
		new[i] = ft_strdup(env->envp_bis[i]);
		i++;
	}
	if (content == NULL)
		new[size] = ft_strdup(variablename);
	else
	{
		new[size] = ft_strjoin(variablename, "=");
		new[size] = ft_strjoin(new[size], content);
	}
	size++;
	new[size] = NULL;
	free_doublepointer(env->envp_bis);
	return (new);
}

// UDPATE VARIABLE
static void	export_variable(char *str, t_env *env)
{
	char	*variable;
	int		len;
	int		i;

	i = 0;
	variable = NULL;
	len = doublepoint_size(env->envp_bis);
	variable = str;
	while (env->envp_bis[i])
	{
		if (ft_strncmp(env->envp_bis[i], variable, ft_strlen(variable) + 1) == 0)
		{
			free (env->envp_bis[i]);
			env->envp_bis[i] = ft_strdup(variable);
			return ;
		}
		i++;
	}
	env->envp_bis = add_variable (env, variable, NULL);
}

// UPDATE VARIABLE
static void	env_variable(char *str, t_env *env)
{
	char	*variablename;
	char	*content;
	int		len;
	int		i;

	i = 0;
	len = doublepoint_size(env->envp_bis);
	variablename = NULL;
	content = NULL;
	variablename = ft_substr(str, 0,
			ft_strlen(str) - ft_strlen(ft_strchr(str, '=')));
	content = ft_substr(str, ft_strlen(variablename) + 1,
			ft_strlen(ft_strchr(str, '=')) + 1);
	printf("CONTENT STRING: %s\n", content);
	if (ft_strlen(content) == 0)
		content = "";
	while (env->envp_bis[i])
	{
		if (ft_strncmp(env->envp_bis[i], variablename,
				ft_strlen(variablename)) == 0)
		{
			free (env->envp_bis[i]);
			env->envp_bis[i] = ft_strjoin(variablename, "=");
			env->envp_bis[i] = ft_strjoin(env->envp_bis[i], content);
			return ;
		}
		i++;
	}
	env->envp_bis = add_variable(env, variablename, content);
}

//cmd[0] = "export";
// IMPORTANT: Last string = NULL
void	command_export(t_child *child, t_env *env)
{
	int	i;

	i = 1;
	if (child->parser_cmd[i] == NULL)
	{
		no_options(env);
		return ; //DONE
	}
	if (invalid_identifier(child->parser_cmd) != 0)
		return ; //DONE
	while (child->parser_cmd[i] && child->parser_cmd)
	{
		if (ft_strchr(child->parser_cmd[i], '=') != NULL)
			env_variable(child->parser_cmd[i], env);
		else
			export_variable(child->parser_cmd[i], env);
		i++;
	}
}