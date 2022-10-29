/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:18:25 by jmatheis          #+#    #+#             */
/*   Updated: 2022/10/29 19:24:12 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static void allocate_cmd_space(t_lex *lex, int i, t_child **child, int k)
// {
// 	int	z;

// 	z = 0;
// 	printf("CMD");
// 	while(ft_strncmp(lex->lexer[i],"<", 2) == 0 && ft_strncmp(lex->lexer[i],"<<", 3) == 0
// 			&& ft_strncmp(lex->lexer[i],">", 2) == 0 && ft_strncmp(lex->lexer[i],">>", 3) == 0
// 			&& ft_strncmp(lex->lexer[i],"|", 2) == 0)
// 		i += 2;
// 	z++;
// 	i++;
// 	printf("NUMBER OF CMD: %d\n", z);
// 	child[k]->parser_cmd = malloc(z * sizeof(char *));
// 	if (child[k]->parser_cmd == NULL)
// 		errorexit("check parser_cmd allocation");
// 	exit(0);
// }

static void	fill_parser_cmd(t_lex *lex, t_child **child)
{
	int	i;
	int j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (k <= lex->noofpipes + 2)
	{
		while (ft_strncmp(lex->lexer[i], "|", 2) != 0 && lex->lexer[i] && lex->lexer)
		{
			while(ft_strncmp(lex->lexer[i],"<", 2) == 0 || ft_strncmp(lex->lexer[i],"<<", 3) == 0
				|| ft_strncmp(lex->lexer[i],">", 2) == 0 || ft_strncmp(lex->lexer[i],">>", 3) == 0)
				i += 2;
			child[k]->parser_cmd[j] = lex->lexer[i];
			i++;
		}
		j = 0;
		i = 0;
		k++;
	}
	exit (0);
}

void	parse_commands(t_lex *lex, t_child **child)
{
	int	i;
	int	k;
	int z;

	i = 0;
	k = 0;
	z = 0;
	while (k <= (lex->noofpipes + 2) && lex->lexer && lex->lexer[i])
	{
		while (ft_strncmp(lex->lexer[i], "|", 2) != 0 && lex->lexer[i])
		{
			while(ft_strncmp(lex->lexer[i],"<", 2) == 0 || ft_strncmp(lex->lexer[i],"<<", 3) == 0
				|| ft_strncmp(lex->lexer[i],">", 2) == 0 || ft_strncmp(lex->lexer[i],">>", 3) == 0)
					i += 2;
			if (lex->lexer[i])
				break ;
			printf("str: %s\n", lex->lexer[i]);
			z++;
			i++;
			printf("Here: %d\n", lex->noofpipes);
		}
		printf("NUMBER OF CMD: %d\n", z);
		// allocate_cmd_space(lex, i, child, k);
		// child[k]->parser_cmd = malloc(z * sizeof(char *));
		// if (child[k]->parser_cmd == NULL)
		// 	errorexit("check parser_cmd allocation");
		z = 0;
		i++;
		k++;
	}
	exit (0);
	fill_parser_cmd(lex, child);
}
// 	k = 0;
// 	j = 0;
// 	while(child && k <= lex->noofpipes + 2)
// 	{
// 		while((*child)->parser_cmd[j])
// 		{
// 			printf("WORKS\n");
// 			printf("child %d: %s\n", k, (*child)->parser_cmd[j]);
// 			j++;
// 		}
// 		j = 0;
// 		(*child)++;
// 		k++;
// 	}
// 	exit (0);
// }
