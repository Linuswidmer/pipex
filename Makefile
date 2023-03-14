NAME = pipex

FILENAMES_PIPEX = main

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

test:
	rm outfile
	touch outfile
	./pipex infile outfile

.PHONY: all clean fclean re

