
#include "../../includes/minishell.h"

/*
	export environment variables
	create new ones & replace old ones
	check them with env
	use unset to remove some of them
	check the result with env
*/

// static char	*builtdelete_quotes(char *str)
// {
// 	if (ft_strtrim(str, "\"") != NULL)
// 		str = ft_strtrim(str, "\"");
// 	if (ft_strtrim(str, "'") != NULL)
// 		str = ft_strtrim(str, "'");
// 	return (str);
// }

static int	invalid_identifier(char **cmd)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (cmd && cmd[i])
	{
		// cmd[i] = builtdelete_quotes(cmd[i]);
		while (cmd[i][j] != '\0')
		{
			if (ft_isdigit(cmd[i][0]) != 0 || cmd[i][0] == '='
				|| ((ft_isalnum(cmd[i][j]) == 0) && cmd[i][j] != '_'
					&& cmd[i][j] != '=' && cmd[i][j] != 39 && cmd[i][j] != '"'))
			{
				ft_putstr_fd("export: '", 2);
				ft_putstr_fd(cmd[i], 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				// printf("export: '%s': not a valid identifier\n", cmd[i]);
				return (1);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

static int	doublepoint_size(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

static void	export_variable(char *str, t_exec *exec)
{
	char	*variable;
	int		len;
	int		i;

	i = 0;
	variable = NULL;
	len = doublepoint_size(exec->envp_bis);
	variable = str;
	while (exec->envp_bis[i])
	{
		if (ft_strncmp(exec->envp_bis[i], variable, ft_strlen(variable)) == 0)
		{
			free (exec->envp_bis[i]);
			exec->envp_bis[i] = ft_strdup(variable);
			return ;
		}
		i++;
	}
	exec->envp_bis[len] = ft_strdup(variable);
	len++;
	exec->envp_bis[len] = NULL;
}

static void	env_variable(char *str, t_exec *exec)
{
	char	*variablename;
	char	*content;
	int		len;
	int		i;

	i = 0;
	len = doublepoint_size(exec->envp_bis);
	variablename = NULL;
	content = NULL;
	variablename = ft_substr(str, 0,
			ft_strlen(str) - ft_strlen(ft_strchr(str, '=')));
	content = ft_substr(str, ft_strlen(variablename) + 1,
			ft_strlen(ft_strchr(str, '=')) + 1);
	// content = builtdelete_quotes(content);
	if (ft_strlen(content) == 0)
		content = "";
	while (exec->envp_bis[i])
	{
		if (ft_strncmp(exec->envp_bis[i], variablename,
				ft_strlen(variablename)) == 0)
		{
			free (exec->envp_bis[i]);
			exec->envp_bis[i] = ft_strjoin(variablename, "=");
			exec->envp_bis[i] = ft_strjoin(exec->envp_bis[i], content);
			return ;
		}
		i++;
	}
	printf("TEST\n");
	exec->envp_bis[len] = ft_strjoin(variablename, "=");
	exec->envp_bis[len] = ft_strjoin(exec->envp_bis[len], content);
	len++;
	exec->envp_bis[len] = NULL;
	int z = 0;
	while (exec->envp_bis[z])
	{
		printf("NEW ENV: %s\n", exec->envp_bis[z]);
		z++;
	}
}

char	*add_quotes(char *adding)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = NULL;
	tmp = ft_calloc(ft_strlen(adding) + 2, sizeof(char));
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
	tmp[j] = '"';
	return (tmp);
}

static void	no_options(t_exec *exec)
{
	int		i;
	char	**export;

	i = 0;
	export = NULL;
	while (exec->envp_bis[i])
		i++;
	export = ft_calloc(i + 1, sizeof(char *));
	if (export == NULL)
		errorexit("Allocation error");
	i = 0;
	while (exec->envp_bis[i])
	{
		if (ft_strchr(exec->envp_bis[i], '=') != NULL)
			export[i] = add_quotes(exec->envp_bis[i]);
		else
			export[i] = exec->envp_bis[i];
		ft_printf("declare -x ");
		ft_printf("%s\n", export[i]);
		i++;
	}
}

//cmd[0] = "export";
// IMPORTANT: Last string = NULL
int	command_export(t_child *child, t_exec *exec)
{
	int	i;

	i = 1;
	if (child->parser_cmd[i] == NULL)
	{
		no_options(exec);
		return (1);
	}
	if (invalid_identifier(child->parser_cmd) != 0)
		return (1);
	while (child->parser_cmd[i] && child->parser_cmd)
	{
		if (ft_strchr(child->parser_cmd[i], '=') != NULL)
			env_variable(child->parser_cmd[i], exec);
		else
			export_variable(child->parser_cmd[i], exec);
		i++;
	}
	return (0);
}
