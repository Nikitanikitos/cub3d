/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 21:36:50 by imicah            #+#    #+#             */
/*   Updated: 2020/06/20 21:36:51 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int8_t	get_texture(char *line, t_img_data *img, void *mlx)
{
	int8_t	fd;

	while (*line == ' ')
		line++;
	if ((fd = open(line, O_RDONLY)) == -1)
		return (TEX_ERR);
	close(fd);
	img->img = mlx_xpm_file_to_image(mlx, line, &img->width, &img->height);
	if (img->img == NULL)
		return (TEX_ERR);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_length,
																&img->endian);
	return (1);
}

int8_t	get_resolution(char *line, int *width, int *height)
{
	int8_t	flag;
	int		resolution[2];
	int		resolution_value;
	int		q;

	q = 0;
	while (*(++line))
		if (ft_isdigit(*line) && flag)
		{
			if ((resolution_value = ft_atoi(line)) >= 100 && q < 2)
				resolution[q++] = resolution_value;
			else
				return (RES_ERR);
			flag = 0;
		}
		else if (*line != ' ' && !ft_isdigit(*line))
			return (RES_ERR);
		else if (!ft_isdigit(*line))
			flag = 1;
	*width = resolution[0];
	*height = resolution[1];
	return (q == 2 ? 1 : RES_ERR);
}

int8_t	get_color(char *line, t_color *rgb)
{
	unsigned char	color[3];
	int				color_value;
	int8_t			flag;
	int				q;

	q = 0;
	while (*(++line))
		if (ft_isdigit(*line) && flag)
		{
			color_value = ft_atoi(line);
			if (0 <= color_value && color_value <= 255 && q < 3)
				color[q++] = (unsigned char)color_value;
			else
				return (COLOR_ERR);
			flag = 0;
		}
		else if (*line != ' ' && *line != ',' && !ft_isdigit(*line))
			return (COLOR_ERR);
		else if (!ft_isdigit(*line))
			flag = 1;
	rgb->r = color[0];
	rgb->g = color[1];
	rgb->b = color[2];
	return (q == 3 ? 1 : COLOR_ERR);
}

int8_t	get_data(char *line, t_game_info *game_info, t_screen *screen)
{
	int8_t	answer;

	answer = 0;
	if (line[0] == 'N' && line[1] == 'O')
		answer = get_texture(line + 2, &(game_info)->textures[0], screen->mlx);
	else if (line[0] == 'W' && line[1] == 'E')
		answer = get_texture(line + 2, &(game_info)->textures[1], screen->mlx);
	else if (line[0] == 'S' && line[1] == 'O')
		answer = get_texture(line + 2, &(game_info)->textures[2], screen->mlx);
	else if (line[0] == 'E' && line[1] == 'A')
		answer = get_texture(line + 2, &(game_info)->textures[3], screen->mlx);
	else if (*line == 'S')
		answer = get_texture(line + 2, &(game_info)->sprite_texture,
																screen->mlx);
	else if (*line == 'R')
		answer = get_resolution(line, &screen->width, &screen->height);
	else if (*line == 'F')
		answer = get_color(line, &game_info->floor_color);
	else if (*line == 'C')
		answer = get_color(line, &game_info->ceiling_color);
	else if (*line)
		answer = UNKNOWN_TOOL;
	free(line);
	return (answer);
}
