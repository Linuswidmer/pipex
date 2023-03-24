# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/17 17:10:01 by lwidmer           #+#    #+#              #
#    Updated: 2023/03/24 11:00:28 by lwidmer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

FILENAMES_PIPEX = pipe pipe_utils init parse parse_utils terminate terminate_utils

SRCS_PIPEX = ./srcs_pipex/
SRCS = $(addprefix $(SRCS_PIPEX), $(addsuffix .c, $(FILENAMES_PIPEX)))

OBJS_PIPEX = ./srcs_pipex/
OBJS = $(addprefix $(OBJS_PIPEX), $(addsuffix .o, $(FILENAMES_PIPEX)))

CFLAGS = -Werror -Wall -Wextra

INCLUDES_DIR = -I ./includes

${NAME}: ${OBJS}
	cc -o ${NAME} $^ -L. ./libft/libft.a

.c.o: ${SRCS}
	cc -c -o $@ $< ${INCLUDES_DIR}

all: ${NAME}

clean:
	rm -rf ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

test_output: all
	make test_output -C ./pipex_tester

test_memory: all
	make test_memory -C ./pipex_tester

memory: all
	valgrind --leak-check=full --track-fds=yes --show-reachable=yes ./pipex infile "grep h" "wc -w" outfile

.PHONY: all clean fclean re

