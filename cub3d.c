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

int 	main(int ac, char **av)
{
	char			*line;
	char			count_arg;
	t_map_data		*map_data;
	const char		fd = (char)open(av[1], O_RDONLY);

	if (ac == 1)
		return((int)write(1, "Error!\n", 6) - 6);
	count_arg = 0;
	map_data = map_data_init();
	while (get_next_line(fd, &line) > 0 && count_arg < 8)
	{
		ac = get_map_data(line, &map_data);
		if (ac == -1)
			exit_failure("Color should be from 0 to 255!", map_data);
		else if (ac == -2)
			exit_failure("Resolution should be from 100", map_data);
		else if (ac == -3)
			exit_failure("Error texture path", map_data);
		count_arg += ac;
	}
	if (count_arg != 8)
		exit_failure("Not enough tools!", map_data);
	else if (write_map(fd, line, map_data) == 0)
		exit_failure("Not valid map!", map_data);
	engine(map_data);
	free_scene_descr(map_data);
	return (0);
}
