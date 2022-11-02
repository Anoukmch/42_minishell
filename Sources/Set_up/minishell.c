/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:42:42 by amechain          #+#    #+#             */
/*   Updated: 2022/11/02 15:59:57 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//char *exit_string;

void	print_lexer(t_lex *lex)
{
	int	i;

	i = 0;
	lex->iter = 0;
	while (lex->lexer[lex->iter])
	{
		printf("%s\n", lex->lexer[lex->iter]);
		lex->iter++;
	}
	printf("%s\n", lex->lexer[lex->iter]);
}

int main(int ac, char **ag, char **envp)
{
    t_lex   *lex;
    t_child **child;
    t_exec  *exec;

    if (ac != 1 || !ag[0])
        errorexit("Wrong number of arguments");
    while (1)
    {
        lex = initialize_lex();
        child = initialize_child(lex);
        exec = initialize_exec(lex, envp);
        if (lex->line && *(lex->line))
            add_history(lex->line);
        parser(lex, child);
    }
    // as soon as ^D --> signal (find needle in haystack function?)
    // giving line to lexer
    return (0);
}

