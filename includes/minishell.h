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

// RETURN 0 --> all fine
// RETURN 1 --> error message, stay in shell
// RETURN 2 --> error message (?), exit shell

extern int	g_exit_code;

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
	int		input_counter;
	char	**parser_redirect_output;
	int		output_counter;
	int		fd_in;
	int		fd_out;
	int		id;
	int		heredoc_quotes;
	char	*command;
	bool	isbuiltin;

}	t_child;

typedef struct s_exec
{
	int		nbr_process;
	int		end[2];
	int		buffer[1];
	int		isheredoc; //are we using it? store if heredoc has quotes?
	pid_t	last_pid;

}	t_exec;

typedef struct s_env
{
	char	**envp_bis;
	char	**envp_path;
	char	*envp_line;
	int		c1;
	int		c2;
	int		c3;
}	t_env;

// CHECKERS
void	print_lexer(t_lex *lex);
void	print_parser(t_child **child);

// FREE
void	free_lex(t_lex	*lex);
void	close_piping(t_exec	*exec);
void	free_struct(t_child	**child, t_exec	*exec);
void	free_array(char **array);
void	free_env(t_env	*env);

// INIT
int		check_syntax(t_lex *lex);
void	count_pipes(t_lex *lex);
t_lex	*initialize_lex(void);
t_child	**initialize_child(t_lex *lex);
t_exec	*initialize_exec(t_lex *lex);
t_env	*initialize_env(char **envp);

char	*delete_quotes(char *str);
int		mark_quotes(char *str, char *before_str);

// SIGNALS
void	handle_signals(void);
void	handle_signals_heredoc(void);
void	signal_for_heredoc(int signum);

// LEXER
void	skipquotes(char *quote, char lex);
char	*convert_tabs_to_spaces(char *str);
void	create_line2(t_lex *lex);
int		lexer_count_spaces(t_lex *lex);

char	**create_lexer_string(t_lex *lex);
char	**split_lexer(char const *s, char c);
void	errorexit(char *message);

// PARSER
int		parser(t_lex *lex, t_child	**child, t_env	*env);
int		parse_commands(t_lex *lex, t_child **child);
int		parser_redirection(t_lex *lex, t_child **child);
int		check_redirection_table(char **array);
// PARSER INIT
t_child	**init_child(t_lex *lex, t_child **child);
void	count_pipes(t_lex *lex);

// EXECUTOR
int		executor(t_child **child, t_exec *exec, t_env *env);
int		processes(t_child *child, t_exec *exec, t_env *env);

int		check_builtins_other(t_child *child);
int		check_builtins_env(t_child *child);
int		get_env_path(t_env *env);
int		get_path_from_env(t_env *env, t_child *child);

// BUILTIN
int		command_env(t_env *env);
int		command_path(t_child *child, t_env *env);
int		command_echo(t_child *child);
int		command_cd(t_child *child);
int		command_pwd(void);
int		command_exit(t_child *child, t_exec *exec);
int		command_export(t_child *child, t_env *env);
int		command_unset(t_child *child, t_env *env);

// ENV
int		doublepoint_size(char **str);
char	**get_position_in_env(t_env *env, char *variable);

// ERROR
int		perror_return(char *str);
void	perror_exit_child(char *str);
void	perror_exit_status(char *str, int status);
int		perror_return_status(char *str, int status);

void	errorexit(char *message);

#endif
