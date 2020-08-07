# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/03 20:01:04 by imicah            #+#    #+#              #
#    Updated: 2020/08/07 18:34:25 by imicah           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = cub
MLX_LIB = libmlx

SRCS    = $(shell find srcs -type f -name '*.c')

OBJS	= $(SRCS:.c=.o)
LIBS    = -L./minilibx -lmlx -lXext -lX11 -lm
MLX		= minilibx/libmlx.a

.PHONY: clean fclean all

all: $(NAME)

$(NAME): $(OBJS)
	gcc ${OBJS} ${LIBS} $(MLX) -o ${NAME}

$(MLX_LIB):
	cd minilibx
	make

%.o : %.c
	gcc -Iheaders -Iminilibx -o $@ -c $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

