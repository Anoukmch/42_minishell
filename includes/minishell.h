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
# include <termios.h>
# include <stdbool.h>
# include <limits.h>

# include "../includes/libs/libs.h"

typedef struct s_lex
{
	char	*line;
	char	*line2;
	char	**lexer;
	int		counter;
	int		no_processes;
	int		iter;
}	t_lex;

/* parser_redirect[0] = infile <
	parser_redirect[1]=> LIMITER for here_doc <<
	parser_redirect[2] = outfile >
	parser_redirec[3] = outfile in append mode >> */
typedef struct s_child
{
	char	**parser_cmd;
	int		no_cmd_opt;
	char	**parser_redirect_input;
	int 	input_counter;
	char	**parser_redirect_output;
	int 	output_counter;
	int		fd_in;
	int		fd_out;
	int		id;
	char	*command;

}	t_child;

typedef struct s_exec
{
	char 	**envp_bis;
	char	**envp_path;
	char	*envp_line;
	int		nbr_process;
	int		end[2];
	int		buffer[1];
	int	isheredoc;
	pid_t	last_pid;

}	t_exec;

void	print_lexer(t_lex *lex);

// INIT
void count_pipes(t_lex *lex);
t_lex *initialize_lex();
t_child **initialize_child(t_lex *lex);
t_exec *initialize_exec(t_lex *lex, char **envp);

char *delete_quotes (char *str);
char *mark_quotes(char *str);

// SIGNALS
void	handle_signals(void);

// LEXER
char	**create_lexer_string(t_lex *lex);
char	**split_lexer(char const *s, char c);
void	errorexit(char *message);
// LEXER FREEING
void	free_doublepointer (char **str);

// PARSER
void	parser(t_lex *lex, t_child	**child);
void	parse_commands(t_lex *lex, t_child **child);
void	parser_redirection(t_lex *lex, t_child **child);
// PARSER INIT
t_child **init_child(t_lex *lex, t_child **child);
void	count_pipes(t_lex *lex);

// EXECUTOR
void	executor(t_lex *lex, t_child **child, t_exec *exec);
void	processes(t_child *child, t_exec *exec);

// BUILTIN
void	command_env(t_exec *exec);
void    command_path(t_lex *lex, t_child **child, t_exec *exec);
void	command_echo(t_child *child, t_exec *exec);
void	command_cd(t_child *child, t_exec *exec);
void	command_pwd(t_exec *exec);
void	command_exit(t_child *child, t_exec *exec);
void	command_export (t_child *child, t_exec *exec);
void	command_unset(t_child *child, t_exec *exec);

void	count_new_spaces(char *line, t_lex *lex);

// MISCELLANEOUS
// void delete_quotes(char **cmd);

// CHECKING LEXER
//void print_lexer(t_lex *lex);
#endif
