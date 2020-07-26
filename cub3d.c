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

char	read_data_file(char *filename, t_map_data *map_data, char **line)
{
	const char		fd = (char)open(filename, O_RDONLY);
	char			count_arg;
	char 			result;

	count_arg = 0;
	while (get_next_line(fd, line) > 0 && count_arg < 8)
	{
		result = get_map_data(*line, map_data);
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
	return (fd);
}

int 	main(int ac, char **av)
{
	char			*line;
	t_map_data		map_data;
	char			fd;

	if (ac == 1)
		exit_failure("Error");
	map_data.mlx = mlx_init();
	fd = read_data_file(av[1], &map_data, &line);
	if (write_map(fd, line, &map_data) == 0)
		exit_failure("Not valid map!");
	engine(map_data, av[ac - 1]);
	return (0);
}
