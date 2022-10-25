/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:50:42 by amechain          #+#    #+#             */
/*   Updated: 2022/06/23 12:46:29 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_substrs(char const *s, char c)
{
	size_t	i;
	size_t	old_i;
	int		count;

	i = 0;
	count = 0;
	while (i < ft_strlen(s))
	{
		while (i < ft_strlen(s))
		{
			if (s[i] != c)
				break ;
			i++;
		}
		old_i = i;
		while (i < ft_strlen(s))
		{
			if (s[i] == c)
				break ;
			i++;
		}
		if (i > old_i)
			count++;
	}
	return (count);
}

static int	count_substr_len(const char *s, char c, int len)
{
	int	i;

	i = 0;
	while (s[len] && s[len] != c)
	{
		i++;
		len++;
	}
	return (i);
}

static char	**check_null_string(int nb_of_strs, char	**arr)
{
	int		string_index;

	string_index = 0;
	while (string_index < nb_of_strs)
	{
		free(arr[string_index]);
		string_index++;
	}
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	int		string_index;
	int		nb_of_strs;
	char	**arr;

	i = 0;
	string_index = 0;
	if (s == NULL)
		return (NULL);
	nb_of_strs = count_substrs(s, c);
	arr = (char **)malloc((nb_of_strs + 1) * sizeof(char *));
	if (arr == NULL)
		return (NULL);
	while (i < ft_strlen(s) && string_index < (nb_of_strs))
	{
		while (s[i] == c)
			i++;
		arr[string_index] = ft_substr(s, i, count_substr_len(s, c, i));
		if (arr[string_index] == NULL)
			return (check_null_string(nb_of_strs, arr));
		string_index++;
		i += count_substr_len(s, c, i);
	}
	arr[string_index] = NULL;
	return (arr);
}
