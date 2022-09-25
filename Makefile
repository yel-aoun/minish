# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/06 13:46:37 by yel-aoun          #+#    #+#              #
#    Updated: 2022/09/25 12:09:49 by yel-aoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = main.c src/ft_builtins.c src/ft_init.c src/ft_exec.c utiles/utiles_1.c utiles/utiles_2.c utiles/ft_tools.c builtins/cd.c builtins/echo.c \
	builtins/env.c builtins/export.c builtins/pwd.c builtins/unset.c exec/execution.c utiles/ft_up.c exec/exec_utils.c exec/exec_tools.c \
	exec/exec_cmd.c builtins/ft_help_export.c utiles/ft_tools_help.c builtins/exit.c parcing/lexer.c parcing/token.c parcing/ft_strlen.c \
	parcing/ft_strcat.c parcing/find_env.c parcing/find_in_env.c parcing/ft_lstadd_back.c parcing/ft_split.c get_next/get_next_line.c \
	get_next/get_next_line_utils.c

CC = cc -Wall -Wextra -Werror  #-g -fsanitize=address 

OBJ = $(SRC:.c=.o)
LIB = libft/libft.a

all :$(NAME)

$(LIB) :
	@cd libft && make

$(NAME) : $(LIB) $(OBJ)
	@$(CC) $(OBJ) $(LIB) -o $(NAME) -lreadline #-L ~/goinfre/.brew/opt/readline/lib -I ~/goinfre/.brew/opt/readline/include  #-fsanitize=address

clean :
	@rm -f $(OBJ) && cd libft && make clean

fclean : clean
	@rm -f $(NAME) && cd libft && make fclean

re : fclean all

.PHONY : all clean fclean re
