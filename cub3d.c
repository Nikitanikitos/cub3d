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

void	free_scene_descr(t_descr *scene_descr) {
	free(scene_descr->map);
	free(scene_descr->textures[0]);
	free(scene_descr->textures[1]);
	free(scene_descr->textures[2]);
	free(scene_descr->textures[3]);
	free(scene_descr->sprite_texture);
	free(scene_descr);
}

t_descr *create_struct(void)
{
	t_descr *scene_descr;

	if (!(scene_descr = (t_descr *)malloc(sizeof(t_descr))))
		return (NULL);
	ft_bzero(scene_descr->celling_color, 3);
	ft_bzero(scene_descr->floor_color, 3);
	return (scene_descr);
}

int 	main(int ac, char **av)
{
	char		*line;
	t_descr		*scene_descr;
	int			count_arg;
	const int	fd = open(av[1], O_RDONLY);

	if (ac != 2)
		return((int)write(1, "ERROR", 5) - 5);
	count_arg = 0;
	scene_descr = create_struct();
	while (get_next_line(fd, &line) > 0)
		if ((count_arg += get_desrc(line, &scene_descr)) == 8)
			break;
	if (count_arg != 8)
		exit(EXIT_FAILURE);
	else
		scene_descr->map = get_map(fd, &line);
	free_scene_descr(scene_descr);
	return (0);
}
