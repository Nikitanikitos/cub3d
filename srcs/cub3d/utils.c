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

void 	close_game(t_cub cub)
{
	char	i;
	void	*img;

	i = 0;
	while (i < 4)
	{
		img = cub.game_info.textures[i++].img;
		mlx_destroy_image(cub.screen.mlx, img);
	}
	mlx_destroy_image(cub.screen.mlx, cub.screen.img_world.img);
	mlx_destroy_image(cub.screen.mlx, cub.game_info.sprite_texture.img);
	mlx_destroy_window(cub.screen.mlx, cub.screen.win);
	free(cub.screen.mlx);
	free(cub.game_info.items);
	free(cub.game_info.map.map);
	exit(0);
}

void	exit_failure(char *error)
{
	write(1, "Error!\n", 7);
	write(1, error, ft_strlen(error));
	write(1, "\n", 1);
	exit(EXIT_FAILURE);
}