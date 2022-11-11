/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:41:59 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/11 10:57:01 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// 1. handle varaibles, then quotes
// INT FUNCTION
// Marking $ signs outside of quotes & in double quotes with -2
int mark_quotes(char *str)
{
	char	quote;
	int		i;

	i = 0;
	quote = '\0';
	while (str[i])
	{
		if (quote == '\0' && str[i] == '\'')
		{
			quote = '\'';
			str[i] = -1;
		}
		else if (quote == '\0' && str[i] == '\"')
		{
			quote = '\"';
			str[i] = -1;
		}
		else if (quote == '\'' && str[i] == '\'')
		{
			quote = '\0';
			str[i] = -1;
		}
		else if (quote == '\"' && str[i] == '\"')
		{
			quote = '\0';
			str[i] = -1;
		}
		else if ((quote == '\"' || quote == '\0') && str[i] == '$')
			str[i] = -2;
		i++;
	}
	if (quote == '\'' || quote == '\"')
	{
		ft_putstr_fd("QUOTES NOT CLOSED\n", 2);
		return (1);
	}
	return (0);
}

char	*delete_quotes(char *str)
{
	int		i;
	int		count;
	char	*final;

	i = 0;
	count = 0;
	final = NULL;
	while (str[i])
	{
		if (str[i] == -1)
			count++;
		i++;
	}
	final = malloc((ft_strlen(str) - count) * sizeof(char));
	if (final == NULL)
		return (NULL);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != -1)
		{
			final[count] = str[i];
			count++;
		}
		i++;
	}
	final[count] = '\0';
	return (final);
}
