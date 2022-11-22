/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_outfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:23:13 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/22 15:23:14 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	open_outfile(t_child *child, int nbr_elements, int i)
{
	while (child->parser_redirect_output[i])
	{
		if (!ft_strcmp(child->parser_redirect_output[i], ">"))
		{
			child->fd_out = open(child->parser_redirect_output[i + 1],
					O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (child->fd_out < 0)
				return (perror_return_msg(child->parser_redirect_output[i + 1],
						1));
			if (i < nbr_elements - 2)
				close(child->fd_out);
		}
		else if (!ft_strcmp(child->parser_redirect_output[i], ">>"))
		{
			child->fd_out = open(child->parser_redirect_output[i + 1],
					O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (child->fd_out < 0)
				return (perror_return_msg(child->parser_redirect_output[i + 1],
						1));
			if (i < nbr_elements - 2)
				close(child->fd_out);
		}
		i += 2;
	}
	return (0);
}

int	get_outfile(t_child *child)
{
	int	i;
	int	nbr_elements;

	i = 0;
	nbr_elements = 0;
	if (child->parser_redirect_output[0] == NULL)
		return (0);
	while (child->parser_redirect_output[nbr_elements])
		nbr_elements++;
	if (open_outfile(child, nbr_elements, i))
		return (1);
	return (0);
}
