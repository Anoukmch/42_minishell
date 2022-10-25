/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:42:42 by amechain          #+#    #+#             */
/*   Updated: 2022/10/25 09:42:57 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
    static char *line = (char *)NULL;
    while (1)
    {
    line = readline("input: ");
    if (line && *line)
        add_history(line);
    if (line == NULL)
        exit(0);
    }
    // as soon as ^D --> signal (find needle in haystack function?)
    // giving line to lexer
    return (0);
}
