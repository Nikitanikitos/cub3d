/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 19:35:45 by imicah            #+#    #+#             */
/*   Updated: 2020/06/13 19:35:47 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	read_data_file(int fd, t_game_info *game_info, t_screen *screen)
{
	char 			*line;
	char			count_arg;
	char 			result;

	count_arg = 0;
	while (get_next_line(fd, &line) > 0 && count_arg < 8)
	{
		result = get_map_data(line, game_info, screen);
		if (result == -1)
			exit_failure("Color should be from 0 to 255!");
		else if (result == -2)
			exit_failure("Resolution should be from 100");
		else if (result == -3)
			exit_failure("Error textures path");
		count_arg += result;
	}
	if (count_arg != 8)
		exit_failure("Not enough tools!");
}

int 	main(int ac, char **av)
{
	const char		fd = (char)open(av[1], O_RDONLY);
	t_game_info		game_info;
	t_screen		screen;

	if (ac == 1)
		exit_failure("Error");
	screen.mlx = mlx_init();
	read_data_file(fd, &game_info, &screen);
	if (write_map(fd, &game_info.map) == 0)
		exit_failure("Not valid map!");
	engine(game_info, screen, av[ac - 1]);
	return (0);
}
