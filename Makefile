# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/17 17:10:01 by lwidmer           #+#    #+#              #
#    Updated: 2023/03/20 16:36:00 by lwidmer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

FILENAMES_PIPEX = pipe pipe_utils parse terminate

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

outfile:
	touch outfile

test: all outfile
	rm outfile
	./pipex infile "grep a" "wc -w" outfile
	cat outfile

test2: all outfile
	rm outfile
	./pipex infile "grep h -v" "wc -w" outfile
	cat outfile

test3: all outfile
	rm outfile
	./pipex infile "grep a" "grep d" outfile
	cat outfile

memory: all
	valgrind --leak-check=full --track-fds=yes --show-reachable=yes ./pipex infile "grep h" "wc -w" outfile

.PHONY: all clean fclean re

