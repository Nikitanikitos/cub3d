# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/03 20:01:04 by imicah            #+#    #+#              #
#    Updated: 2020/08/03 20:46:28 by imicah           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = cub

SRCS    = cub3d.c srcs/libft/ft_realloc.c \
					srcs/libft/ft_strlen.c \
					srcs/libft/ft_strdup.c \
					srcs/libft/ft_bzero.c \
					srcs/libft/ft_atoi.c \
					srcs/libft/ft_strcpy.c \
					srcs/libft/ft_calloc.c \
					srcs/libft/ft_strjoin.c \
					srcs/libft/ft_strchr.c \
					srcs/libft/ft_lstnew.c \
					srcs/libft/ft_strncmp.c \
					srcs/libft/ft_memcpy.c \
					srcs/libft/ft_itoa.c \
					srcs/get_next_line/get_next_line.c \
					srcs/get_next_line/get_next_line_utils.c \
					srcs/cub3d/init.c \
					srcs/cub3d/utils.c \
					srcs/cub3d/get_map_data.c \
					srcs/cub3d/get_map.c \
					srcs/cub3d/engine/engine.c \
					srcs/cub3d/engine/count_dist_to_wall/count_dist_to_wall.c \
					srcs/cub3d/engine/engine_utils.c \
					srcs/cub3d/engine/draw/drawing_map.c \
					srcs/cub3d/engine/draw/drawing.c \
					srcs/cub3d/bmp.c \
					srcs/cub3d/engine/count_dist_to_wall/dist_to_wall_vertical.c \
					srcs/cub3d/engine/count_dist_to_wall/dist_to_wall_horizontal.c \
					srcs/cub3d/engine/count_dist_to_wall/distance_utils.c

OBJS	= $(SRCS:.c=.o)
LIBS    = -lXext -lX11 -lm -L./minilibx -lmlx
MLX		= minilibx/libmlx_Linux.a

.PHONY: clean fclean all

all: $(NAME)

$(NAME): $(OBJS)
	gcc ${OBJS} ${LIBS} $(MLX) -o ${NAME}

%.o : %.c
	gcc -Iheaders -Iminilibx -o $@ -c $<

re:
	rm $(OBJS)
