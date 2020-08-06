/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 21:36:56 by imicah            #+#    #+#             */
/*   Updated: 2020/06/20 21:36:57 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		copy_read_map(char *map, char *line, int i)
{
	static char	flag;

	while (*line)
	{
		if ((ft_strchr(PLAYER_POS, *line) && flag) || !ft_strchr(MAP_CHAR, *line))
		{
			free(map);
			return (0);
		}
		else
		{
			if (ft_strchr(PLAYER_POS, *line))
				flag = 1;
			map[i++] = *line++;
		}
	}
	map[i++] = '\n';
	map[i] = 0;
	return (i);
}

char	*read_map(char *line, char *temp_map, t_map *map)
{
	static int	i;
	int			current_length;

	if (*line)
	{
		current_length = ft_strlen(line);
		if (current_length > map->line_length)
			map->line_length = current_length;
		temp_map = ft_realloc(temp_map, (int)current_length + 2);
		if ((i = copy_read_map(temp_map, line, i)) == 0)
			return (NULL);
	}
	return (temp_map);
}

char	*copy_write_map(char *map, char *temp_map, int length_line)
{
	const int	k = ft_strlen(temp_map);
	int		current_length_line;
	int		i;
	int		q;

	i = 0;
	q = 0;
	current_length_line = 0;
	while (i < k)
	{
		if (temp_map[i] == '\n')
		{
			while (current_length_line++ < length_line)
				map[q++] = ' ';
			i++;
			current_length_line = 0;
		}
		map[q++] = temp_map[i++];
		current_length_line++;
	}
	--q;
	map[q] = 0;
	return (map);
}

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

int8_t	read_map_data(char fd, t_game_info *game_info, t_map *map)
{
	char	*temp_map;
	char 	*line;

	game_info->number_sprites = 0;
	map->column_length = 0;
	map->line_length = 0;
	temp_map = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		game_info->number_sprites += get_number_sprites(line);
		temp_map = read_map(line, temp_map, map);
		free(line);
		if (temp_map == NULL)
			return (0);
		map->column_length++;
	}
	if (map->column_length < 3 || map->line_length < 3)
		return (0);
	free(line);
	map->map = ft_calloc(sizeof(char),
						 (map->line_length * map->column_length) + 1);
	map->map = copy_write_map(map->map, temp_map, map->line_length);
	free(temp_map);
	return (1);
}
