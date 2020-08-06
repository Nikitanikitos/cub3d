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

# include "cub3d.h"

int8_t	check_valid_map_ne(int x, int y, t_map map_info, char *map)
{
	int		index;
	int8_t	result_e;
	int8_t	result_n;

	index = y * map_info.line_length + x;
	if (x > map_info.line_length || y > map_info.column_length ||
		x < 0 || y < 0 || map[index] == ' ' || map[index] == 0)
		return (0);
	else if (map[index] == '1')
		return (1);
	result_n = check_valid_map_ne(x, y -1, map_info, map);
	result_e = check_valid_map_ne(x + 1, y, map_info, map);
	return (result_e == 1 && result_n == 1);
}

int8_t	check_valid_map_nw(int x, int y, t_map map_info, char *map)
{
	int		index;
	int8_t	result_w;
	int8_t	result_n;

	index = y * map_info.line_length + x;
	if (x > map_info.line_length || y > map_info.column_length ||
		x < 0 || y < 0 || map[index] == ' ' || map[index] == 0)
		return (0);
	else if (map[index] == '1')
		return (1);
	result_n = check_valid_map_nw(x, y - 1, map_info, map);
	result_w = check_valid_map_nw(x - 1, y, map_info, map);
	return (result_w == 1 && result_n == 1);
}

int8_t		check_valid_map_sw(int x, int y, t_map map_info, char *map)
{
	int		index;
	int8_t	result_s;
	int8_t	result_w;

	index = y * map_info.line_length + x;
	if (x > map_info.line_length || y > map_info.column_length ||
		x < 0 || y < 0 || map[index] == ' ' || map[index] == 0)
		return (0);
	else if (map[index] == '1')
		return (1);
	result_s = check_valid_map_sw(x, y + 1, map_info, map);
	result_w = check_valid_map_sw(x - 1, y, map_info, map);
	return (result_s == 1 && result_w == 1);
}

int8_t		check_valid_map_se(int x, int y, t_map map_info, char *map)
{
	int		index;
	int8_t	result_e;
	int8_t	result_s;

	index = y * map_info.line_length + x;
	if (x > map_info.line_length || y > map_info.column_length ||
		x < 0 || y < 0 || map[index] == ' ' || map[index] == 0)
		return (0);
	else if (map[index] == '1')
		return (1);
	result_s = check_valid_map_se(x, y + 1, map_info, map);
	result_e = check_valid_map_se(x + 1, y, map_info, map);
	return (result_e == 1 && result_s == 1);
}

int8_t	check_valid_map(int x, int y, t_map map_info, char *map)
{
	if (check_valid_map_ne(x, y, map_info, map) &&
		check_valid_map_nw(x, y, map_info, map) &&
		check_valid_map_se(x, y, map_info, map) &&
		check_valid_map_sw(x, y, map_info, map))
		return (1);
	else
		return (0);
}
