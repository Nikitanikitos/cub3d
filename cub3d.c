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
	char		*line;
	t_descr		*scene_descr;
	int			count_arg;
	const int	fd = open(av[1], O_RDONLY);

	if (ac == 1)
		return((int)write(1, "Error!\n", 6) - 6);
	count_arg = 0;
	scene_descr = create_struct();
	while (get_next_line(fd, &line) > 0)
		if ((count_arg += get_desrc(line, &scene_descr)) == 8)
			break;
	if (count_arg != 8)
		exit_failure("Not enough tools!", scene_descr);
	else if ((scene_descr->map = get_map(fd, &line)) == NULL)
		exit_failure("Not valid map!", scene_descr);
	engine(scene_descr);
	free_scene_descr(scene_descr);
	return (0);
}
