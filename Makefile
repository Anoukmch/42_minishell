# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/25 09:30:39 by amechain          #+#    #+#              #
#    Updated: 2022/11/02 15:47:35 by amechain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Werror -Wextra #-lreadline  #-fsanitize=address -g

NAME =  minishell

M_SRC = Set_up/minishell.c \
		Set_up/initialize_child.c \
		Set_up/initialize_exec.c \
		Set_up/initialize_lex.c \
		Lexer/lexer.c \
		Lexer/lexer_split.c \
		Lexer/freeing.c \
		Parser/parser.c \
		Parser/parser_command.c \
		Parser/parser_init.c \
		Parser/parser_redirection.c

M_SRCS = $(addprefix ./Sources/, $(M_SRC))

M_OBJS = $(M_SRCS:.c=.o)

LIBS_DIR = ./includes/libs

LIBS_NAME = libs.a

all: $(NAME)

bonus : $(BONUS)

$(NAME): $(M_OBJS) $(LIBS_DIR)/$(LIBS_NAME)
	$(CC) $(CFLAGS) $^ -o $@ -lreadline

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
