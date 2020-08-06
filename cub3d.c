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

void	read_game_data(int fd, t_game_info *game_info, t_screen *screen)
{
	char	*line;
	int8_t	count_arg;
	int8_t 	answer;

	count_arg = 0;
	while (get_next_line(fd, &line) > 0 && count_arg < COUNT_ARG)
	{
		answer = get_data(line, game_info, screen);
		if (answer == COLOR_ERR)
			exit_failure("Color should be from 0 to 255!");
		else if (answer == RES_ERR)
			exit_failure("Resolution should be from 100");
		else if (answer == TEX_ERR)
			exit_failure("Error textures path");
		count_arg += answer;
	}
	free(line);
	if (count_arg != COUNT_ARG)
		exit_failure("Not enough tools!");
}

int 	main(int ac, char **av)
{
	const int8_t	fd = (char)open(av[1], O_RDONLY);
	t_game_info		game_info;
	t_screen		screen;

	if (ac == 1)
		exit_failure("Error");
	else if (fd == -1)
		exit_failure("Error file");
	screen.mlx = mlx_init();
	read_game_data(fd, &game_info, &screen);
	if (read_map_data(fd, &game_info, &game_info.map) == 0)
		exit_failure("Not valid map!");
	engine(game_info, screen, av[ac - 1]);
	return (0);
}
