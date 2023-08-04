# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/28 17:24:19 by mberrouk          #+#    #+#              #
#    Updated: 2023/08/03 20:30:59 by hoakoumi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC			=	cc

CFALGS		=	-Wall -Wextra -Werror -fsanitize=address -g3

IDFLAG		=	-I/Users/hoakoumi/homebrew/opt/readline/include

LDFLAG		=	-L/Users/hoakoumi/homebrew/opt/readline/lib -lreadline

SRCS =  utils/ft_split.c utils/linked_list_utils.c utils/utils_double_ptr.c utils/utils_err.c \
		utils/utils_strings.c utils/utils_strings1.c parsing/lexer.c parsing/parser.c parsing/parsing_utils.c\
		main.c exec_test.c parsing/expansion_analysis.c parsing/expansion_in_doublq.c parsing/expansion_utils.c\
		Builtins/builtins.c Builtins/pwd.c Builtins/env.c Builtins/echo.c Builtins/exit.c \
		Builtins/outils_built.c Builtins/unset.c Builtins/cd.c Builtins/export.c Builtins/outils_buit1.c  Builtins/outils_buils2.c 

OBJ = ${SRCS:%.c=%.o}

CC = cc #-Wall -Wextra -Werror  #-lncurses -fsanitize=address -g3 -L -lreadline -L /Users/mberrouk/homebrew/opt/readline/include/readline -I ~/homebrew/opt/readline/include
CFLAGS = -Wall -Wextra -Werror -lncurses -lreadline

all : ${NAME}

${NAME} : ${OBJ}
	$(CC) $(CFALGS) $(IDFLAG) $(LDFLAG) -o $@ $^
	make clean
	#./minishell

%.o : %.c
	$(CC) $(CFALGS) -c $< -o $@ $(IDFLAG)

clean :
	rm -f ${OBJ}

fclean : clean
	rm -f ${NAME}

re : fclean all