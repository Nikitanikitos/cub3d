/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_get_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 02:22:10 by imicah            #+#    #+#             */
/*   Updated: 2020/08/25 02:22:11 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_number_sprites(char *line)
{
	int	result;

	result = 0;
	while (*line)
	{
		if (*line == '2')
			result++;
		line++;
	}
	return (result);
}

int8_t	check_end_file(int8_t fd)
{
	char	*line;

	while (get_next_line(fd, &line) > 0)
	{
		if (*line != '\0')
			return (1);
		free(line);
	}
	free(line);
	return (0);
}

int8_t	check_line_map(char *line, char *temp_map)
{
	if (!*line && temp_map)
		return (1);
	while (*line)
	{
		if (*line == '1' || *line == '0' || *line == '2' ||
			*line == 'W' || *line == 'N' || *line == 'S' || *line == 'E')
			return (0);
		line++;
	}
	return (1);
}

void	map_init(t_map *map, t_game_info *game_info, char **temp_map)
{
	map->line_length = 0;
	map->column_length = 0;
	game_info->number_sprites = 0;
	*temp_map = NULL;
}
