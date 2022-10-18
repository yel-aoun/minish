# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/06 13:46:37 by yel-aoun          #+#    #+#              #
#    Updated: 2022/10/17 12:41:02 by yel-aoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = main.c src/ft_builtins.c src/ft_init.c src/ft_exec.c utiles/utiles_1.c \
	utiles/utiles_2.c utiles/ft_tools.c builtins/cd.c builtins/echo.c \
	builtins/env.c builtins/export.c builtins/pwd.c builtins/unset.c \
	exec/execution.c utiles/ft_up.c exec/exec_utils.c exec/exec_tools.c \
	exec/exec_cmd.c builtins/ft_help_export.c utiles/ft_tools_help.c \
	builtins/exit.c parcing/lexer.c parcing/token.c parcing/ft_strlen.c \
	parcing/ft_strcat.c parcing/find_env.c parcing/find_in_env.c \
	parcing/ft_lstadd_back.c parcing/ft_split.c exec/exec_cmd_help.c \
	exec/execution_help.c exec/execution_help_2.c exec/ft_check_access.c \
	builtins/unset_help.c parcing/help_main1.c parcing/help_main2.c \
	parcing/help_main3.c parcing/lexer2.c parcing/lexer3.c src/ft_help1_exec.c \
	src/ft_help2_exec.c parcing/parc_help.c parcing/__help.c

CC = cc -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)
LIB = libft/libft.a

all :$(NAME)

$(LIB) :
	@cd libft && make

$(NAME) : $(LIB) $(OBJ)
	@$(CC) $(OBJ) $(LIB) -lreadline -o $(NAME) -L ~/goinfre/.brew/opt/readline/lib -I ~/goinfre/.brew/opt/readline/include 
	@echo "\033[0;35mCOMPILED SUCCESSFULY \033[0m"
%.o: %.c
	@$(CC) -c $< -o $@
clean :
	@rm -f $(OBJ) && cd libft && make clean

fclean : clean
	@rm -f $(NAME) && cd libft && make fclean

re : fclean all

.PHONY : all clean fclean re
