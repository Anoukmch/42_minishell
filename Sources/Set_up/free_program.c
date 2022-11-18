#include "../../includes/minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	free_struct (t_child **child, t_exec	*exec, t_env *env)
{
	int	i;

	i = 0;
	if (child)
	{
		while (child[i])
		{
			free_array(child[i]->parser_cmd);
			free_array(child[i]->parser_redirect_input);
			free_array(child[i]->parser_redirect_output);
			free(child[i]->command);
			free(child[i]);
			i++;
		}
		free(child);
	}
	free_array(env->envp_path);
	free(env->envp_line);
	if (exec)
		free(exec);
}

void	close_piping(t_exec	*exec)
{
	if (exec->nbr_process > 1)
	{
		close(exec->end[0]);
		close(exec->end[1]);
	}
}

void	free_lex(t_lex	*lex)
{
	free(lex->line);
	free(lex->line2);
	free_array(lex->lexer);
	free(lex);
}

void	free_env(t_env	*env)
{
	free_array(env->envp_bis);
	free_array(env->envp_path);
	free(env->envp_line);
	free(env);
}
