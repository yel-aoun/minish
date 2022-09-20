SRC = parcing/lexer.c parcing/token.c parcing/ft_strlen.c parcing/ft_strcat.c parcing/find_env.c parcing/find_in_env.c parcing/ft_lstadd_back.c parcing/ft_split.c

CFLAGS = -Wall -Wextra -Werror 

NAME = minishell

OBJ = ${SRC:.c=.o}
LIB = libft.a

all : $(NAME)
$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lreadline -L ~/goinfre/.brew/opt/readline/lib -I ~/goinfre/.brew/opt/readline/include  #-fsanitize=address
clean :
	rm -f $(OBJ)
fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY:	all clean fclean re