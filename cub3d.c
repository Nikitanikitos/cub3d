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
	t_descr			*scene_descr;
	const short		fd = (short)open(av[1], O_RDONLY);

	if (ac == 1)
		return((int)write(1, "Error!\n", 6) - 6);
	count_arg = 0;
	scene_descr = create_struct();
	while (get_next_line(fd, &line) > 0)
	{
		ac = get_desrc(line, &scene_descr);
		if ((count_arg += ac) == 8)
			break;
		else if (ac == -1)
			exit_failure("Error color", scene_descr);
		else if (ac == -2)
			exit_failure("Error resolution", scene_descr);
	}
	if (count_arg != 8)
		exit_failure("Not enough tools!", scene_descr);
	else if ((scene_descr->lengh_line = write_map(fd, &line, &scene_descr->map)) == 0)
		exit_failure("Not valid map!", scene_descr);
//	engine(scene_descr);
	free_scene_descr(scene_descr);
	return (0);
}
