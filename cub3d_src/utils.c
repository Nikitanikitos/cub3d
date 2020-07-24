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
#include "engine.h"

void	free_scene_descr(t_map_data *map_data)
{
	free(map_data->mlx);
	if (map_data->map)
		free(map_data->map);
	free(map_data);
}

void	free_player(t_player *player)
{
	free(player);
}

void	exit_failure(char *error, t_map_data *map_data)
{
	write(1, "Error!\n", 7);
	write(1, error, ft_strlen(error));
	write(1, "\n", 1);
	free_scene_descr(map_data);
	exit(EXIT_FAILURE);
}