#include "../../includes/minishell.h"

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
