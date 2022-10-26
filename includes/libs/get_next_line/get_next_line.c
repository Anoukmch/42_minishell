/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:09:10 by amechain          #+#    #+#             */
/*   Updated: 2022/10/06 16:20:31 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list_char	*store[10240];
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	line = NULL;
	read_and_store(fd, &store[fd]);
	if (store[fd] == NULL)
		return (NULL);
	extract_line(store[fd], &line);
	clean_store(&store[fd]);
	if (line[0] == 0)
	{
		delete_store(store[fd]);
		store[fd] = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

void	read_and_store(int fd, t_list_char **store)
{
	char	*buf;
	int		read_ret;

	read_ret = 1;
	while (!findnewline(*store) && read_ret != 0 && read_ret != -1)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buf == NULL)
			return ;
		read_ret = (int)read(fd, buf, BUFFER_SIZE);
		if (read_ret == 0 || read_ret == -1)
			free(buf);
		else
		{
			buf[read_ret] = '\0';
			buf_to_store(store, buf, read_ret);
			free(buf);
		}
	}
}

void	buf_to_store(t_list_char**store, char *buf, int read_ret)
{
	int			i;
	t_list_char	*last;
	t_list_char	*new;

	new = malloc(sizeof(t_list_char));
	if (new == NULL)
		return ;
	new->next = NULL;
	new->content = malloc(sizeof(char) * (read_ret + 1));
	if (new->content == NULL)
		return ;
	i = 0;
	while (buf[i] && i < read_ret)
	{
		new->content[i] = buf[i];
		i++;
	}
	new->content[i] = '\0';
	if (*store == NULL)
	{
		*store = new;
		return ;
	}
	last = ft_lstlast_char(*store);
	last->next = new;
}

void	extract_line(t_list_char*store, char **line)
{
	int	i;
	int	j;

	if (store == NULL)
		return ;
	measure_store(line, store);
	if (*line == NULL)
		return ;
	j = 0;
	while (store)
	{
		i = 0;
		while (store->content[i] && store->content[i] != '\n')
		{
			(*line)[j++] = store->content[i++];
		}
		if (store->content[i] == '\n')
		{
			(*line)[j] = store->content[i];
			j++;
			break ;
		}
		store = store->next;
	}
	(*line)[j] = '\0';
}

void	clean_store(t_list_char**store)
{
	t_list_char	*last;
	t_list_char	*new;
	int			i;
	int			j;

	i = 0;
	j = 0;
	new = malloc(sizeof(t_list_char));
	if (new == NULL || store == NULL)
		return ;
	new->next = NULL;
	last = ft_lstlast_char(*store);
	while (last->content[i] && last->content[i] != '\n' && last->content)
		i++;
	if (last->content[i] == '\n')
		i++;
	new->content = malloc(sizeof(char) * (ft_strlen(last->content) - i) + 1);
	if (new->content == NULL)
		return ;
	while (last->content[i])
		new->content[j++] = last->content[i++];
	new->content[j] = '\0';
	delete_store(*store);
	*store = new;
}
