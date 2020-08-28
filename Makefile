# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/03 20:01:04 by imicah            #+#    #+#              #
#    Updated: 2020/08/13 14:55:30 by imicah           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = cub3D

SRCS    = $(shell find srcs -type f -name '*.c')

OBJS	= $(SRCS:.c=.o)
LIBS    = -L./minilibx -lmlx -lXext -lX11 -lm
MLX		= minilibx/libmlx.a

.PHONY: clean fclean all bonus

all:    $(NAME)

$(NAME): $(OBJS) $(MLX)
	gcc  -Wall -Wextra -Werror ${OBJS} ${LIBS} $(MLX) -o ${NAME}

$(MLX):
	$(MAKE) -C minilibx

%.o :   %.c
	gcc -Wall -Wextra -Werror -Iheaders -Iminilibx -o $@ -c $<

bonus:  all

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:     fclean all
