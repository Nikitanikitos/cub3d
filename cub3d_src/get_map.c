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

unsigned short	copy_read_map(char *map, char *line, unsigned short i)
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

char			*read_map(char *line, char *map_temp, t_map_data *map_data)
{
	static unsigned short	i;
	unsigned short			temp_length;

	if (*line)
	{
		temp_length = ft_strlen(line);
		if (temp_length > map_data->length_line)
			map_data->length_line = temp_length;
		map_temp = ft_realloc(map_temp, (int)temp_length + 2);
		i = copy_read_map(map_temp, line, i);
	}
	return (map_temp);
}

char			*copy_write_map(char *map, char *map_temp, unsigned short length_line)
{
	unsigned short i;
	unsigned short q;
	unsigned short k;

	i = 0;
	q = 0;
	k = 0;
	while (map_temp[i])
	{
		if (map_temp[i] == '\n')
		{
			while (k++ < length_line)
				map[q++] = ' ';
			i++;
			k = 0;
		}
		map[q++] = map_temp[i++];
		k++;
	}
	--q;
	map[q] = 0;
	return (map);
}

char			write_map(char fd, char *line, t_map_data *map_data)
{
	char			*map_temp;
	unsigned short	count_line;

	count_line = 0;
	map_temp = NULL;
	free(line);
	while (get_next_line(fd, &line) > 0)
	{
		map_temp = read_map(line, map_temp, map_data);
		count_line++;
		free(line);
	}
	free(line);
	map_data->map = ft_calloc(sizeof(char), (map_data->length_line * count_line) + 1);
	map_data->map = copy_write_map(map_data->map, map_temp, map_data->length_line);
	free(map_temp);
	return (1);
}