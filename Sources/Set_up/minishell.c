/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:42:42 by amechain          #+#    #+#             */
/*   Updated: 2022/10/31 10:44:56 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int main(void)
{

    t_lex   *lex;
    // t_child **child;
    static char *line = (char *)NULL;

    lex = ft_calloc(1, sizeof(t_lex));
    // child = ft_calloc(1, sizeof(t_child *));
    if (lex == NULL)
        errorexit("check initializiation of structs");
    while (1)
    {
        line = readline("input: ");
        if (line && *line)
            add_history(line);
        create_lexer_string(line, lex);
        parser(lex);
        if (line == NULL)
            exit(0);
    }
    // as soon as ^D --> signal (find needle in haystack function?)
    // giving line to lexer
    return (0);
}

/* Initialize the struct */
