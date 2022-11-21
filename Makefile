

CC = cc

CFLAGS = -Wall -Werror -Wextra -I /goinfre/$(USER)/.brew/opt/readline/include #-lreadline -fsanitize=address -g

NAME =  minishell

M_SRC = set_up/minishell.c \
		set_up/init/init_child.c \
		set_up/init/init_exec.c \
		set_up/init/init_lex.c \
		set_up/init/init_env.c \
		set_up/signals.c \
		set_up/quotes.c \
		lexer/syntax.c \
		lexer/lex_utils.c \
		lexer/count_spaces.c \
		lexer/create_lexline2.c \
		parser/parser.c \
		parser/parser_command.c \
		parser/parser_redirection.c \
		parser/var_handler/count_size_var.c \
		parser/var_handler/var_handler.c \
		parser/var_handler/fill_var.c \
		parser/var_handler/rebuild_lex.c \
		parser/var_handler/var_handler_utils.c \
		parser/var_handler_heredoc/count_size_var_hd.c \
		parser/var_handler_heredoc/fill_var_hd.c \
		parser/var_handler_heredoc/var_handler_utils_hd.c \
		parser/quote_handler/quote_handler.c \
		executor/environment_path.c \
		executor/builtin_check.c \
		executor/executor.c \
		executor/process/process.c \
		executor/process/child_exec.c \
		executor/process/do_command.c \
		executor/process/get_infile.c \
		executor/process/get_outfile.c \
		executor/process/process_utils.c \
		executor/process/single_builtin.c \
		executor/builtin/builtin_cd.c \
		executor/builtin/builtin_echo.c \
		executor/builtin/builtin_env.c \
		executor/builtin/builtin_exit.c \
		executor/builtin/builtin_export.c \
		executor/builtin/builtin_export_utils.c \
		executor/builtin/builtin_pwd.c \
		executor/builtin/builtin_unset.c \
		executor/builtin/builtin_utils.c \
		executor/heredoc/get_heredoc.c \
		executor/heredoc/heredoc_utils.c \
		executor/get_command.c \
		utils/exit_return_status.c \
		utils/utils.c \
		utils/free_program.c \

M_SRCS = $(addprefix ./sources/, $(M_SRC))

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
