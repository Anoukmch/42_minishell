/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:09:05 by amechain          #+#    #+#             */
/*   Updated: 2022/10/06 17:37:31 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list_char	*ft_lstlast_char(t_list_char *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	findnewline(t_list_char *store)
{
	int				i;
	t_list_char		*tocheck;

	if (store == NULL)
		return (0);
	tocheck = ft_lstlast_char(store);
	i = 0;
	while (tocheck->content[i])
	{
		if (tocheck->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	delete_store(t_list_char *store)
{
	t_list_char	*next;

	while (store)
	{
		free(store->content);
		next = store->next;
		free(store);
		store = next;
	}
}

void	measure_store(char **line, t_list_char *store)
{
	int	i;
	int	len;

	len = 0;
	while (store)
	{
		i = 0;
		while (store->content[i] && store->content[i] != '\n')
		{
			len++;
			i++;
		}
		if (store->content[i] == '\n')
		{
			len++;
			break ;
		}
		store = store->next;
	}
	*line = malloc(sizeof(char) * (len + 1));
}
