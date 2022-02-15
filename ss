#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zoizmer <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/05 22:28:16 by zoizmer           #+#    #+#              #
#    Updated: 2022/02/14 22:30:57 by rlahmaid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = ./libft/libft.a
SRCS = env_utils.c my_redirections.c my_builtins2.c my_utils2.c my_utils.c ft_strcmp.c my_builtins_functions.c my_ft_excution.c main.c env_strct.c scan.c print_strct.c parser.c rmquotes.c parser_utils.c parser_utils2.c parser_utils3.c data_proccessing.c data_proccessing_utils.c free.c
FLAGS= -lreadline  -I /Users/milmi/.brew/opt/readline/include -Wall -Wextra -Werror -g -fsanitize=address
HOMEENVFLAGS= -g -lreadline -L /usr/local/opt/readline/lib -I /usr/local/opt/readline/include -Wall -Wextra -Werror -g -fsanitize=address
VALGRIND= -lreadline -L /Users/milmi/.brew/opt/readline/lib -I /Users/milmi/.brew/opt/readline/include -Wall -Wextra -Werror
rm = rm -f
CC = gcc -g

all : $(NAME)

$(NAME) : $(LIBFT)
	@$(CC) $(FLAGS) $(LIBFT) $(SRCS) $(LIBFT) -o $(NAME)

$(LIBFT):
	@make -C libft

valgrind: fclean $(LIBFT)
	@$(CC) $(VALGRIND) $(LIBFT) $(SRCS) $(LIBFT) -o $(NAME)
	@valgrind --leak-check=full ./minishell
clean :
	
fclean : clean
	@$(rm) $(NAME)
	@make -C libft fclean
	@$(rm) libft.a
	@$(rm) -rf *.dSYM a.out

re: fclean all

run: re
	@./$(NAME)

.PHONY: all bonus both clean fclean re
