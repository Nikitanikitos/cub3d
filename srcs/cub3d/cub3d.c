/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 19:35:45 by imicah            #+#    #+#             */
/*   Updated: 2020/08/17 20:18:31 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	read_game_data(int fd, t_game_info *game_info, t_screen *screen)
{
	char	*line;
	int8_t	count_arg;
	int8_t	answer;

	count_arg = 0;
	while (get_next_line(fd, &line) > 0 && count_arg < COUNT_ARG)
	{
		answer = get_data(line, game_info, screen);
		if (answer == COLOR_ERR)
			exit_with_error(COLOR_ERR);
		else if (answer == RES_ERR)
			exit_with_error(RES_ERR);
		else if (answer == TEX_ERR)
			exit_with_error(TEX_ERR);
		else if (answer == UNKNOWN_TOOL)
			exit_with_error(UNKNOWN_TOOL);
		count_arg += answer;
	}
	free(line);
	if (count_arg < COUNT_ARG)
		exit_with_error(LESS_ARG_ERR);
}

int		main(int ac, char **av)
{
	const int8_t	fd = (char)open(av[1], O_RDONLY);
	t_game_info		game_info;
	t_screen		screen;

	check_arguments(fd, ac, av);
	if (ac == 1)
		exit_with_error(ARG_ERR);
	else if (fd == -1)
		exit_with_error(FILE_ERR);
	screen.mlx = mlx_init();
	read_game_data(fd, &game_info, &screen);
	if (read_map_data(fd, &game_info, &game_info.map) == 0)
		exit_with_error(MAP_ERR);
	if (check_end_file(fd))
		exit_with_error(UNKNOWN_TOOL);
	close(fd);
	engine(game_info, screen, av[2]);
	return (0);
}
