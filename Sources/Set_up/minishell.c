/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:42:42 by amechain          #+#    #+#             */
/*   Updated: 2022/10/27 17:50:05 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int main(void)
{
    t_lex   *lex;
    t_child **child;

    lex = NULL;
    child = NULL;
    static char *line = (char *)NULL;
    while (1)
    {
    line = readline("input: ");
    if (line && *line)
        add_history(line);
    create_lexer_string(line, lex);
    parser(lex, child);
    if (line == NULL)
        exit(0);
    }
    // as soon as ^D --> signal (find needle in haystack function?)
    // giving line to lexer
    return (0);
}

/* Initialize the struct */
