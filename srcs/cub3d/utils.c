/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 15:56:16 by imicah            #+#    #+#             */
/*   Updated: 2020/06/16 15:56:17 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int8_t	check_valid_map_recursion(int x, int y, t_map map_info, char *map)
{
	int		index;
	int8_t	result_n;
	int8_t	result_e;
	int8_t	result_s;
	int8_t	result_w;

	index = y * map_info.line_length + x;
	if (x > map_info.line_length || y > map_info.column_length ||
		x < 0 || y < 0 || map[index] == ' ' || map[index] == 0)
		return (0);
	else if (map[index] == '1' || map[index] == '.')
		return (1);
	map[index] = '.';
	result_n = check_valid_map_recursion(x, y - 1, map_info, map);
	result_s = check_valid_map_recursion(x, y + 1, map_info, map);
	result_w = check_valid_map_recursion(x + 1, y, map_info, map);
	result_e = check_valid_map_recursion(x - 1, y, map_info, map);
	return (result_e && result_s && result_n && result_w);
}

int8_t	check_valid_map(t_player player)
{
	char	*temp_map;

	temp_map = ft_strdup(player.map.map);
	if (!check_valid_map_recursion((int)player.x / 64, (int)player.y / 64,
									player.map, temp_map))
		return (0);
	free(temp_map);
	return (1);
}

void	check_arguments(int8_t fd, int ac, char **av)
{
	int		len_arg;

	if (ac == 1)
		exit_with_error(ARG_ERR);
	else if (fd == -1)
		exit_with_error(FILE_ERR);
	len_arg = ft_strlen(av[1]);
	if (av[1][len_arg - 1] != 'b' && av[1][len_arg - 2] != 'u' &&
			av[1][len_arg - 3] != 'c' && av[1][len_arg - 4] != '.')
		exit_with_error(FORMAT_ERR);
	else if ((ac == 3 && ft_strcmp(av[2], "--save")) || ac > 3)
		exit_with_error(UNKNOWN_ERR);
}

void	close_game(t_cub cub)
{
	int8_t	i;
	void	*img;

	i = 0;
	while (i < 4)
	{
		img = cub.game_info.textures[i++].img;
		mlx_destroy_image(cub.screen.mlx, img);
	}
	mlx_destroy_image(cub.screen.mlx, cub.screen.img_world.img);
	mlx_destroy_image(cub.screen.mlx, cub.game_info.sprite_texture.img);
	mlx_destroy_window(cub.screen.mlx, cub.screen.win);
	free(cub.game_info.sprites);
	free(cub.player.map.map);
	exit(EXIT_SUCCESS);
}

void	exit_with_error(int8_t error_nbr)
{
	const char *errors[11] = {"Color should be from 0 to 255",
							"Resolution should be from 100",
							"Wrong texture path",
							"Not enough tools",
							"Double tools",
							"No file name argument",
							"Invalid file",
							"Invalid map",
							"Unknown argument",
							"Wrong file format",
							"Unknown tool"};

	error_nbr -= 2;
	write(1, "Error!\n", 7);
	write(1, errors[error_nbr], ft_strlen(errors[error_nbr]));
	write(1, "\n", 1);
	exit(EXIT_FAILURE);
}
