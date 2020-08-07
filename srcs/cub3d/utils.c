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

int		close_game(t_cub cub)
{
	int8_t	i;
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
	exit(EXIT_SUCCESS);
}

void	exit_with_error(int error_nbr)
{
	const char *errors[8] = {"Color should be from 0 to 255",
							"Resolution should be from 100",
							"Wrong texture path",
							"Not enough tools",
							"Double tools",
							"No file name argument",
							"Invalid file",
							"Invalid map"};

	error_nbr -= 2;
	write(1, "Error!\n", 7);
	write(1, errors[error_nbr], ft_strlen(errors[error_nbr]));
	write(1, "\n", 1);
	exit(EXIT_FAILURE);
}
