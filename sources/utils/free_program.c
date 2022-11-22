/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Free_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:26:43 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/22 15:26:44 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	free_child(t_child *child, t_exec *exec, t_lex *lex)
{
	if (child)
	{
		free_array(child->parser_cmd);
		free_array(child->parser_redirect_input);
		free_array(child->parser_redirect_output);
		free(child->command);
		free(child->file_buff);
		free(child);
	}
	if (exec)
		free(exec);
	if (lex)
	{
		free(lex->line);
		free(lex->line2);
		free_array(lex->lexer);
		free(lex);
	}
}

void	free_struct(t_child **child, t_exec *exec, t_lex *lex)
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
			free(child[i]->file_buff);
			free(child[i++]);
		}
		free(child);
	}
	if (exec)
		free(exec);
	if (lex)
	{
		free(lex->line);
		free(lex->line2);
		free_array(lex->lexer);
		free(lex);
	}
}

void	free_env(t_env	*env)
{
	free_array(env->envp_bis);
	free(env);
}

t_lex	*free_struct_lex(t_lex *lex)
{
	if (!lex)
		return (NULL);
	if (lex->line)
		free(lex->line);
	if (lex->line2)
		free(lex->line2);
	if (lex->lexer)
		free_array(lex->lexer);
	if (lex)
		free(lex);
	return (NULL);
}
