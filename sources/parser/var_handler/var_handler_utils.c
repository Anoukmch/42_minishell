#include "../../../includes/minishell.h"

char	*is_variable_in_env(char *var, t_env *env)
{
	int	i;

	i = 0;
	while (env->envp_bis[i])
	{
		if (!ft_strncmp(var, env->envp_bis[i], ft_strlen(var)))
		{
			if (env->envp_bis[i][ft_strlen(var)] == '='
				|| env->envp_bis[i][ft_strlen(var)] == '\0')
				return (env->envp_bis[i]);
		}
		i++;
	}
	return (NULL);
}

int	nbr_dollar_sign(char *lex_string)
{
	int	size;
	int	count;

	count = 0;
	size = ft_strlen(lex_string) - 1;
	while (size >= 0)
	{
		if (lex_string[size] == -2)
			count++;
		size--;
	}
	return (count);
}

int	size_env_var(char *all_env_var, int *j)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (all_env_var[i])
	{
		if (all_env_var[i] == '=')
		{
			if (j)
				*j = i + 1;
			size = ft_strlen(all_env_var) - i - 1;
			return (size);
		}
		i++;
	}
	if (j)
		*j = i;
	return (0);
}

char	*fill_env_var(char *all_env_var)
{
	int		j;
	int		size;
	char	*env_var;

	j = 0;
	size = size_env_var(all_env_var, &j);
	env_var = ft_substr(all_env_var, j, size);
	if (!env_var)
		return (NULL);
	return (env_var);
}

int	set_up_new_arg(t_env *env, int sizearg)
{
	env->new_arg = NULL;
	env->new_arg = ft_calloc((sizearg + 1), sizeof(char));
	if (!env->new_arg)
		return (1);
	env->c1 = 0;
	env->c3 = 0;
	return (0);
}
