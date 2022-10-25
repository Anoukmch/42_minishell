/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:09:08 by amechain          #+#    #+#             */
/*   Updated: 2022/09/21 14:34:29 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include "../libs.h"

typedef struct s_list_char
{
	char				*content;
	struct s_list_char	*next;
}					t_list_char;

char		*get_next_line(int fd);
void		clean_store(t_list_char **store);
void		delete_store(t_list_char *store);
void		extract_line(t_list_char *store, char **line);
void		measure_store(char **line, t_list_char *store);
void		buf_to_store(t_list_char **store, char *buf, int read_ret);
int			findnewline(t_list_char *store);
t_list_char	*ft_lstlast_char(t_list_char *lst);
void		read_and_store(int fd, t_list_char **stash);

#endif
