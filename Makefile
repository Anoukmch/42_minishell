

CC = cc

CFLAGS = -Wall -Werror -Wextra -I /goinfre/$(USER)/.brew/opt/readline/include #-lreadline -fsanitize=address -g

NAME =  minishell

M_SRC = Set_up/Minishell.c \
		Set_up/Init/Init_child.c \
		Set_up/Init/Init_exec.c \
		Set_up/Init/Init_lex.c \
		Set_up/Init/Init_env.c \
		Set_up/Signals.c \
		Set_up/Quotes.c \
		Lexer/Syntax.c \
		Lexer/Lex_utils.c \
		Lexer/Count_spaces.c \
		Lexer/Create_lexline2.c \
		Parser/Parser.c \
		Parser/Parser_command.c \
		Parser/Parser_redirection.c \
		Parser/Var_handler/Count_size_var.c \
		Parser/Var_handler/Var_handler.c \
		Parser/Var_handler/Fill_var.c \
		Parser/Var_handler/Rebuild_lex.c \
		Parser/Var_handler/Var_handler_utils.c \
		Parser/Var_handler_heredoc/Count_size_var_hd.c \
		Parser/Var_handler_heredoc/Fill_var_hd.c \
		Parser/Var_handler_heredoc/Var_handler_utils_hd.c \
		Parser/Quote_handler/Quote_handler.c \
		Executor/Environment_path.c \
		Executor/Builtin_check.c \
		Executor/Executor.c \
		Executor/Process/Process.c \
		Executor/Process/Child_exec.c \
		Executor/Process/Do_command.c \
		Executor/Process/Get_infile.c \
		Executor/Process/Get_outfile.c \
		Executor/Process/Process_utils.c \
		Executor/Process/Single_builtin.c \
		Executor/Builtin/Builtin_cd.c \
		Executor/Builtin/Builtin_echo.c \
		Executor/Builtin/Builtin_env.c \
		Executor/Builtin/Builtin_exit.c \
		Executor/Builtin/Builtin_export.c \
		Executor/Builtin/Builtin_export_utils.c \
		Executor/Builtin/Builtin_pwd.c \
		Executor/Builtin/Builtin_unset.c \
		Executor/Builtin/Builtin_utils.c \
		Executor/Heredoc/Get_heredoc.c \
		Executor/Heredoc/Heredoc_utils.c \
		Executor/Get_command.c \
		Utils/Exit_return_status.c \
		Utils/Utils.c \
		Utils/Free_program.c \

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
