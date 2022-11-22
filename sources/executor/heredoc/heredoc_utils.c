/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:22:52 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/22 15:22:53 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	line_null_hd(t_child *child, char *temp)
{
	dup2(child->set_stdin_back, STDIN_FILENO);
	close(child->set_stdin_back);
	unlink(child->file_buff);
	close(child->file);
	free(temp);
	free(child->heredoc_line);
	return (1);
}

int	clean_heredoc(t_child *child, char *temp, int i, int nbr_elements)
{
	close(child->set_stdin_back);
	close(child->file);
	free(temp);
	free(child->heredoc_line);
	if (i < nbr_elements - 2)
		unlink(child->file_buff);
	return (0);
}
