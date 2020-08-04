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

char	*read_map(char *line, char *map_temp, t_map *map)
{
	static int	i;
	int			temp_length;

	if (*line)
	{
		temp_length = ft_strlen(line);
		if (temp_length > map->line_length)
			map->line_length = temp_length;
		map_temp = ft_realloc(map_temp, (int)temp_length + 2);
		if ((i = copy_read_map(map_temp, line, i)) == 0)
			return (NULL);
	}
	return (map_temp);
}

char	*copy_write_map(char *map, char *map_temp, int length_line)
{
	int		i;
	int		q;
	int		current_length_line;
	int 	k = ft_strlen(map_temp);

	i = 0;
	q = 0;
	current_length_line = 0;
	while (i < k)
	{
		if (map_temp[i] == '\n')
		{
			while (current_length_line++ < length_line)
				map[q++] = ' ';
			i++;
			current_length_line = 0;
		}
		map[q++] = map_temp[i++];
		current_length_line++;
	}
	--q;
	map[q] = 0;
	return (map);
}

int		get_number_items(char *line)
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

char	write_map(char fd, t_game_info *game_info, t_map *map)
{
	char	*map_temp;
	int		count_line;
	char 	*line;

	count_line = 0;
	game_info->number_items = 0;
	map->line_length = 0;
	while (get_next_line(fd, &line) > 0)
	{
		game_info->number_items += get_number_items(line);
		map_temp = read_map(line, map_temp, map);
		free(line);
		if (map_temp == NULL)
			return (0);
		count_line++;
	}
	free(line);
	map->map = ft_calloc(sizeof(char),
						 (map->line_length * count_line) + 1);
	map->map = copy_write_map(map->map, map_temp, map->line_length);
	free(map_temp);
	return (1);
}
