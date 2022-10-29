/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:51:36 by amechain          #+#    #+#             */
/*   Updated: 2022/10/29 19:58:37 by amechain         ###   ########.fr       */
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
	int		counter;
	int		noofpipes;
	int		spaces;
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
	int		fd_in;
	int		fd_out;

}	t_child;

// INIT
void count_pipes(t_lex *lex);
// LEXER
void	create_lexer_string(char *line, t_lex *lex);
char	**split_lexer(char const *s, char c);
void	errorexit(char *message);

// PARSER
void	parser(t_lex *lex, t_child **child);
void	parse_commands(t_lex *lex, t_child **child);

void	count_new_spaces(char *line, t_lex *lex);

// CHECKING LEXER
void print_lexer(t_lex *lex);
#endif
