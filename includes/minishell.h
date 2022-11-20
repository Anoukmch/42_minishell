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

extern int	g_exit_code;

typedef struct s_lex
{
	char	*line;
	char	*line2;
	char	**lexer;
	char	**lexer_c;
	int		counter;
	int		no_processes;
	int		iter;
}	t_lex;

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
	int		isheredoc;
	pid_t	last_pid;
	bool	hasfreed;

}	t_exec;

typedef struct s_env
{
	char	**envp_bis;
	char	**envp_path;
	char	*envp_line;
	int		c1;
	int		c2;
	int		c3;
	char	*new_arg;

}	t_env;

// CHECKERS
void	print_lexer(t_lex *lex);
void	print_parser(t_child **child);

// SET_UP/INIT
int		check_syntax(t_lex *lex);
void	count_pipes(t_lex *lex);
t_lex	*initialize_lex(void);
t_child	**initialize_child(t_lex *lex);
t_exec	*initialize_exec(t_lex *lex);
t_env	*initialize_env(char **envp);
char	*delete_quotes_indir(t_child *child, t_lex *lex);
int		mark_quotes_cmds_and_outdir(char *str);
char	*delete_quotes_cmds_and_outdir(char *str);

// SET_UP/SIGNALS
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

// PARSER
int		parser(t_lex *lex, t_child	**child, t_env	*env);
int		parse_commands(t_lex *lex, t_child **child);
int		parser_redirection(t_lex *lex, t_child **child);
int		check_redirection_table(char **array);

// PARSER/QUOTE_HANDLER
int		mark_variables(char *str, char *str_before);
int		check_dollarsign(char *str);
int		quotes_after_dollarsign(t_lex *lex, int no);

// PARSER/VAR_HANDLER
char	*is_variable_in_env(char *var, t_env *env);
int		size_env_var(char *all_env_var, int *j);
char	*fill_env_var(char *all_env_var);
int		set_up_new_arg(t_env *env, int sizearg);
char	**rebuild_lex(t_lex *lex);
char	*handle_var(char *lex_string, t_env *env);
int		nbr_dollar_sign(char *lex_string);
int		nbr_dollar_sign_hd(char *lex_string);
int		size_new_arg(char *lex_string, int count, t_env *env);
int		count_new_arg_env_var(char *var, t_env *env, int *size);
int		fill_new_arg_env_var(char *var, t_env *env);
int		size_new_arg_hd(char *lex_string, int count, t_env *env);
char	*handle_var_hd(char *lex_string, t_env *env);
int		var_handler(t_lex *lex, t_env *env);

// EXECUTOR
int		executor(t_child **child, t_exec *exec, t_env *env, t_lex *lex);

int		check_builtins_other(t_child *child);
int		check_builtins_env(t_child *child);
int		get_env_path(t_env *env);
int		get_path_from_env(t_env *env, t_child *child);

int		get_heredoc(t_child **child, t_exec *exec, t_env *env);

// EXECUTOR/PROCESS
int		processes(t_child *child, t_exec *exec, t_env *env, t_lex *lex);
int		single_builtin(t_child *child, t_exec *exec, t_env *env, t_lex *lex);
int		child_exec(t_child *child, t_exec *exec, t_env *env, t_lex *lex);
int		get_infile(t_child *child);
int		get_outfile(t_child *child);
int		switch_put(t_child *child, t_exec *exec);
void	close_pipe(t_exec *exec, t_child *child);
int		builtin_command(t_child *child, t_exec *exec, t_env *env, t_lex	*lex);
void	env_command(t_child *child, t_env *env);

// BUILTIN
int		command_env(t_env *env);
int		command_path(t_child *child, t_env *env);
int		command_echo(t_child *child);
int		command_cd(t_child *child);
int		command_pwd(void);
int		command_exit(t_child *child, t_exec *exec, t_env *env, t_lex *lex);
int		command_export(t_child *child, t_env *env);
int		command_unset(t_child *child, t_env *env);
char	*add_quotes(char *adding);
int		no_options(t_env *env);
int		is_only_digits(char *str);
bool	ft_atoilong(long long int *buffer, char *s);
// EXPORT
int		replace_variable(t_env *env, char *variable, char *content);
int		add_new_variable(char **new, int *size, char *variablename, char *content);
char	**create_new_env(t_env *env, char *variablename, char *content);

// ENV
int		doublepoint_size(char **str);
char	**get_position_in_env(t_env *env, char *variable);

// UTILS
void	perror_exit_status(char *str, int status);
int		perror_return_status(char *str, int status);
void	close_piping(t_exec	*exec);
void	free_struct(t_child **child, t_exec *exec, t_lex *lex);
void	free_array(char **array);
void	free_env(t_env *env);
#endif
