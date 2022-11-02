/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:59:04 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/02 13:45:20 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parser(t_lex *lex)
{
	t_child	**child;
	int k;
	int i;

	i = 0;
	k = 0;
	child = NULL;
	child = init_child(lex, child);
	parse_commands(lex, child);
	parser_redirection(lex, child);
	exit(0);
}

//  grep "hello world" >outfile
