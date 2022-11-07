/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:59:04 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/07 16:38:08 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	parser(t_lex *lex, t_child	**child)
{
	int k;
	int i;

	i = 0;
	k = 0;
	parse_commands(lex, child);
	parser_redirection(lex, child);
	// while (child[k])
    // {
    //     i = 0;
    //     while (i < child[k]->no_cmd_opt)
    //         printf("parser cmd for child %d : %s\n", k, child[k]->parser_cmd[i++]);
    //     i = 0;
    //     if (!child[k]->input_counter)
    //         printf("No redirection input\n");
    //     while (i < child[k]->input_counter)
    //         printf("parser input for child %d : %s\n", k, child[k]->parser_redirect_input[i++]);
    //     i = 0;
    //     if (!child[k]->output_counter)
    //         printf("No redirection output\n");
    //     while (i < child[k]->output_counter)
    //         printf("parser output for child %d : %s\n", k, child[k]->parser_redirect_output[i++]);
    //     k++;
    // }
}

//  grep "hello world" >outfile
