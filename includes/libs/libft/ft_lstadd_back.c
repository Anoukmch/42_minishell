/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 09:10:19 by amechain          #+#    #+#             */
/*   Updated: 2022/04/26 10:18:41 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*buffer;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	buffer = ft_lstlast(*lst);
	buffer->next = new;
}
