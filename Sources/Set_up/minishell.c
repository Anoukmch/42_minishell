/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:42:42 by amechain          #+#    #+#             */
/*   Updated: 2022/10/29 19:05:15 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int main(void)
{

    t_lex   *lex;
    t_child **child;
    static char *line = (char *)NULL;

    lex = ft_calloc(1, sizeof(t_lex));
    if (lex == NULL)
        errorexit("check initializiation of structs");
    printf("TEST");
    while (1)
    {
        line = readline("input: ");
        if (line && *line)
            add_history(line);
        create_lexer_string(line, lex);
        count_pipes(lex);
        child = ft_calloc(lex->noofpipes + 2, (lex->noofpipes + 2) * sizeof(char *));
        if (child == NULL)
            errorexit("check initializiation of structs");
        parser(lex, child);
        if (line == NULL)
            exit(0);
    }
    // as soon as ^D --> signal (find needle in haystack function?)
    // giving line to lexer
    return (0);
}

/* Initialize the struct */
