#include "../../../includes/minishell.h"

char	*get_var_hd(char *lex_string, t_env *env)
{
	char	*var;

	while (lex_string[env->c1] && lex_string[env->c1] != '$')
		env->new_arg[env->c3++] = lex_string[env->c1++];
	if (!lex_string[env->c1])
		return (NULL);
	env->c2 = env->c1 + 1;
	if (lex_string[env->c2] == '?')
	{
		var = ft_substr(lex_string, env->c1 + 1, 1);
		env->c2++;
	}
	else
	{
		while (lex_string[env->c2] && (ft_isalnum(lex_string[env->c2])
				|| lex_string[env->c2] == '_'))
			env->c2++;
		var = ft_substr(lex_string, env->c1 + 1, (env->c2 - env->c1 - 1));
	}
	return (var);
}

int	fill_new_arg_hd(char *lex_string, t_env *env)
{
	char	*var;

	var = get_var_hd(lex_string, env);
	if (!var || !var[0])
		return (1);
	if (fill_new_arg_env_var(var, env))
		return (1);
	free(var);
	env->c1 = env->c2;
	return (0);
}

char	*handle_var_hd(char *lex_string, t_env *env)
{
	int	k;
	int	count;
	int	sizearg;

	k = 0;
	count = nbr_dollar_sign_hd(lex_string);
	sizearg = size_new_arg_hd(lex_string, count, env);
	if (sizearg == -1)
		return (NULL);
	if (set_up_new_arg(env, sizearg))
		return (NULL);
	while (k < count && sizearg != 0)
	{
		if (fill_new_arg_hd(lex_string, env))
			return (NULL);
		k++;
	}
	while (lex_string[env->c2] != '\0' && sizearg != 0)
		env->new_arg[env->c3++] = lex_string[env->c2++];
	env->new_arg[env->c3] = '\0';
	free(lex_string);
	lex_string = ft_strdup(env->new_arg);
	free(env->new_arg);
	return (lex_string);
}
