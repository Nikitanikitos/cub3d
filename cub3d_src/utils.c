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

void	free_scene_descr(t_descr *scene_descr)
{
	if (scene_descr->map != NULL)
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
	ft_bzero(scene_descr->resolution, 2);
	return (scene_descr);
}

void	exit_failure(char *error, t_descr *scene_descr)
{
	write(1, "Error!\n", 7);
	write(1, error, ft_strlen(error));
	write(1, "\n", 1);
	free_scene_descr(scene_descr);
	exit(EXIT_FAILURE);
}