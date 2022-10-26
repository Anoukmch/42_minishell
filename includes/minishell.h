/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:51:36 by amechain          #+#    #+#             */
/*   Updated: 2022/10/26 15:02:42 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# include "../includes/libs/libs.h"

typedef struct s_lex
{
	char	*line2;
	char	**lexer;
	int		nbr_tokens;
	int		counter;
}	t_lex;

/* parser_redirect[0] = infile <
	parser_redirect[1]=> LIMITER for here_doc <<
	parser_redirect[2] = outfile >
	parser_redirec[3] = outfile in append mode >> */
typedef struct s_child
{
	char	**parser_cmd;
	char	**parser_redirect_input;
	char	**parser_redirect_output;
}	t_child;


void	create_lexer_string(char *line, t_lex *lex);
void parser(t_lex *lex, t_child *child);

#endif
