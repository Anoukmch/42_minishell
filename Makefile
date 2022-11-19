

CC = gcc

CFLAGS = -Wall -Werror -Wextra -I /goinfre/$(USER)/.brew/opt/readline/include #-lreadline -fsanitize=address -g

NAME =  minishell

M_SRC = Set_up/minishell.c \
		Set_up/initialize_child.c \
		Set_up/initialize_exec.c \
		Set_up/initialize_lex.c \
		Set_up/initialize_env.c \
		Set_up/signals.c \
		Set_up/quotes.c \
		Set_up/checker.c \
		Set_up/syntax.c \
		Set_up/free_program.c \
		Lexer/lex_helpers.c \
		Lexer/count_spaces.c \
		Lexer/create_lexline2.c \
		Parser/parser.c \
		Parser/parser_command.c \
		Parser/parser_redirection.c \
		Parser/Var_handler/Count_size_var.c \
		Parser/Var_handler/Expand_variable.c \
		Parser/Var_handler/Fill_var.c \
		Parser/Var_handler/Rebuild_lex.c \
		Parser/Var_handler/Var_handler_utils.c \
		Parser/Var_handler_heredoc/Count_size_var_hd.c \
		Parser/Var_handler_heredoc/Fill_var_hd.c \
		Parser/Var_handler_heredoc/Var_handler_utils_hd.c \
		Executor/environment_path.c \
		Executor/command_check.c \
		Executor/builtin_check.c \
		Executor/builtin_export_no_args.c \
		Executor/executor.c \
		Executor/processes.c \
		Executor/builtin.c \
		Executor/builtin_export.c \
		Executor/builtin_unset.c \
		Executor/exitstatus.c

M_SRCS = $(addprefix ./Sources/, $(M_SRC))

M_OBJS = $(M_SRCS:.c=.o)

LIBS_DIR = ./includes/libs

LIBS_NAME = libs.a

all: $(NAME)

bonus : $(BONUS)

$(NAME): $(M_OBJS) $(LIBS_DIR)/$(LIBS_NAME)
	$(CC) $(CFLAGS) $^ -o $@ -lreadline -L /goinfre/$(USER)/.brew/opt/readline/lib

$(LIBS_DIR)/$(LIBS_NAME):
	make -sC $(LIBS_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(LIBS_DIR)
	@rm -f $(M_OBJS)

fclean: clean
	make fclean -C $(LIBS_DIR)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
