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

char			*copy_read_map(char *map, char *line, unsigned short *i)
{
	char	flag;

	flag = 0;
	while (*line)
	{
		if (ft_strchr(PLAYER_POS, *line) && flag || !ft_strchr(MAP_CHAR, *line))
		{
			free(map);
			return (NULL);
		}
		else
		{
			flag = ft_strchr(PLAYER_POS, *line);
			map[(*i)++] = *line++;
		}
	}
	map[(*i)++] = '\n';
	map[*i] = 0;
	return (map);
}

char			*read_map(int fd, char **line)
{
	char			*map;
	unsigned short	i;

	i = 0;
	map = NULL;
	free(*line);
	while (get_next_line(fd, line) > 0)
	{
		if (**line)
		{
			map = ft_realloc(map, (int)ft_strlen(*line) + 2);
			map = copy_read_map(map, *line, &i);
		}
		free(*line);
	}
	free(*line);
	return (map);
}

unsigned short	count_data(char *map_temp, unsigned short *lengh_line)
{
	unsigned short 	i;
	unsigned short	q;
	unsigned short	count_line;

	i = 0;
	*lengh_line = 0;
	count_line = 0;
	while (map_temp[i])
	{
		if ((q = (short)ft_strchr(map_temp + i, '\n')) > *lengh_line)
			*lengh_line = q - 1;
		count_line++;
		if (q == 0)
			return (--count_line);
		i += q;
	}
	return (count_line);
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
	map[--q] = 0;
	return (map);
}

char		write_map(int fd, char **line, char **map, unsigned short *length_line)
{
	char			*map_temp;
	unsigned short	count_line;

	if ((map_temp = read_map(fd, line)) == NULL)
		return (0);
	count_line = count_data(map_temp, length_line);
	*map = ft_calloc(sizeof(char), (*length_line * count_line) + 1);
	*map = copy_write_map(*map, map_temp, *length_line);
	free(map_temp);
	return (1);
}