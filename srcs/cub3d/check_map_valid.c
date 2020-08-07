/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_valid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 23:18:23 by imicah            #+#    #+#             */
/*   Updated: 2020/08/05 23:18:23 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int8_t	check_valid_map_recursion(int x, int y, t_map map_info, char *map)
{
	int		index;
	int8_t	result_n;
	int8_t	result_e;
	int8_t	result_s;
	int8_t	result_w;

	index = y * map_info.line_length + x;
	if (x > map_info.line_length || y > map_info.column_length ||
		x < 0 || y < 0 || map[index] == ' ' || map[index] == 0)
		return (0);
	else if (map[index] == '1' || map[index] == '.')
		return (1);
	map[index] = '.';
	result_n = check_valid_map_recursion(x, y - 1, map_info, map);
	result_s = check_valid_map_recursion(x, y + 1, map_info, map);
	result_w = check_valid_map_recursion(x + 1, y, map_info, map);
	result_e = check_valid_map_recursion(x - 1, y, map_info, map);
	return (result_e && result_s && result_n && result_w);
}

int8_t	check_valid_map(t_player player)
{
	char	*temp_map;

	temp_map = ft_strdup(player.map.map);
	if (!check_valid_map_recursion((int)player.x / 64, (int)player.y / 64,
														player.map, temp_map))
		return (0);
	free(temp_map);
	return (1);
}
