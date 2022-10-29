/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 16:05:43 by jmatheis          #+#    #+#             */
/*   Updated: 2022/10/29 18:46:57 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//counting the words to reserve the storage with malloc
static size_t	wordcounter(char const *s, char c)
{
	size_t	i;
	size_t	counter;

	i = 0;
	counter = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != '\0')
			counter++;
		while (s[i] != c && s[i] != '\0')
		{
			// COUNT RIGHT BECAUSE OF QUOTES
			i++;
		}
	}
	return (counter);
}

//length of substring for every word
//returning the last word with strlen of address of s[start]
//other words using strchr as length of substr
//&s[start] --> whole string beginning with start
//difference from strchr & &s[start]-->string to return/length
static size_t	endsofsubs(char const *s, char c, size_t start)
{
	if (ft_strchr(s + start, c) == NULL)
		return (ft_strlen(&s[start]));
	// else if(s[start] == '"' && ft_strchr(s + start + 1, '"') == 0)
	// 	errorexit("NO CLOSING DOUBLE QUOTES");
	else
	{
		if (s[start] == '"')
			return (ft_strchr(s + start + 1, '"') - &s[start] + 1);
		else if (s[start] == 39)
			return (ft_strchr(s + start + 1, 39) - &s[start] + 1);
		else
			return (ft_strchr(s + start, c) - &s[start]);
	}
}

//freeing the buffer
static char	**bufferfree(char **buffer)
{
	size_t	i;

	i = 0;
	while (buffer[i] != NULL)
	{
		free(buffer[i]);
		i++;
	}
	free(buffer);
	return (NULL);
}

//skipping c
//creating substrings in buffer
//adding length to string position
char	**split_lexer(char const *s, char c)
{
	char	**buffer;
	size_t	i;
	size_t	start;

	i = 0;
	start = 0;
	if (s == NULL)
		return (NULL);
	buffer = malloc((wordcounter(s, c) + 1) * sizeof(char *));
	if (buffer == NULL)
		return (NULL);
	while (s[start] != '\0')
	{
		while (s[start] == c)
			start++;
		if (s[start] == '\0')
			break ;
		buffer[i] = (ft_substr(s, start, endsofsubs(s, c, start)));
		if (buffer[i] == NULL)
			return (bufferfree(buffer));
		i++;
		if (s[start] == '"' || s[start] == 39)
			start += endsofsubs(s, c, start) + 1;
		else
			start += endsofsubs(s, c, start);
	}
	buffer[i] = NULL;
	return (buffer);
}


//  grep "hello world" >outfile