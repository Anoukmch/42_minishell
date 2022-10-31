/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:59:04 by jmatheis          #+#    #+#             */
/*   Updated: 2022/10/31 13:21:55 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parser(t_lex *lex)
{
	t_child	**child;

	child = NULL;
	child = init_child(lex, child);
	parse_commands(lex, child);
	exit(0);
}

//  grep "hello world" >outfile