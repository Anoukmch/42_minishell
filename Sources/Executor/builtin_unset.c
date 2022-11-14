
#include "../../includes/minishell.h"

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
		if (cmd[i][0] == '\0')
			printf("unset: '%s': not a valid identifier\n", cmd[i]);
		while (cmd[i][j] != '\0')
		{
			if (ft_isdigit(cmd[i][0]) != 0 || cmd[i][0] == '='
				|| (ft_isalnum(cmd[i][j]) == 0 && cmd[i][j] != '_'
					&& cmd[i][j] != '=' && cmd[i][j] != 39 && cmd[i][j] != '"'))
			{
				ft_putstr_fd("unset: '", 2);
				ft_putstr_fd(cmd[i], 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				// printf("unset: '%s': not a valid identifier\n", cmd[i]);
				return (1);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

char	**get_position_in_env(t_exec *exec, char *variable)
{
	int	i;

	i = 0;
	while (exec->envp_bis[i])
	{
		if (ft_strncmp(exec->envp_bis[i], variable,
				ft_strlen(variable) + 1) == 0)
		{
			return (&exec->envp_bis[i]);
		}
		i++;
	}
	return (NULL);
}

int	command_unset(t_child *child, t_exec *exec)
{
	int		i;
	int		j;
	char	**tmp;

	i = 1;
	tmp = NULL;
	if (child->parser_cmd[i] == NULL)
		return (0);
	if (invalid_identifier(child->parser_cmd) != 0)
		return (0);
	while (child->parser_cmd[i])
	{
		j = 0;
		tmp = get_position_in_env(exec, child->parser_cmd[i]);
		free(tmp[j]);
		j++;
		while (tmp[j])
		{
			tmp[j - 1] = tmp[j];
			j++;
		}
		tmp[j - 1] = NULL;
		i++;
	}
	return (0);
}
