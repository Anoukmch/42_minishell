/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:06:11 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/10 17:04:35 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


// double quote & single quote must be handled differently
/* inserts spaces when sign & filename should be seperated
ASCII 39 = single quote*/

// HANDLE DOUBLE QUOTES WITH SPACES IN IT!!
// cat<<Makefile grep"hello world"| cat>>outfile
// < "Makefile" cat >outfile
// grep "a"b"" --> works for hello ab
/* takes input string and splits it into tokens*/


// CHECKING LEXER
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
