# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zoizmer <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/05 22:28:16 by zoizmer           #+#    #+#              #
#    Updated: 2021/12/05 22:28:20 by zoizmer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = libft.a
SRCS = my_ft_excution.c main.c env_strct.c scan.c print_strct.c parser.c rmquotes.c parser_utils.c parser_utils2.c parser_utils3.c data_proccessing.c data_proccessing_utils.c free.c
FLAGS= -g -lreadline -L /Users/milmi/.brew/opt/readline/lib -I /Users/milmi/.brew/opt/readline/include -Wall -Wextra -Werror -fsanitize=address
HOMEENVFLAGS= -g -lreadline -L /usr/local/opt/readline/lib -I /usr/local/opt/readline/include -Wall -Wextra -Werror -fsanitize=address
VALGRIND= -lreadline -L /Users/milmi/.brew/opt/readline/lib -I /Users/milmi/.brew/opt/readline/include -Wall -Wextra -Werror
rm = rm -f
CC = gcc

all : $(NAME)

$(NAME) : $(LIBFT)
	$(CC) $(FLAGS) $(LIBFT) $(SRCS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C libft
	cp libft/libft.a .

valgrind: fclean $(LIBFT)
	$(CC) $(VALGRIND) $(LIBFT) $(SRCS) $(LIBFT) -o $(NAME)
	valgrind --leak-check=full ./minishell
clean :
	
fclean : clean
	@$(rm) $(NAME)
	make -C libft fclean
	$(rm) libft.a

re: fclean all

.PHONY: all bonus both clean fclean re
