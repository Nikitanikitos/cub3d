/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 19:35:45 by imicah            #+#    #+#             */
/*   Updated: 2020/06/13 19:35:47 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"
#include "libft.h"

t_descr *create_struct(void)
{
	t_descr *scene_descr;

	if (!(scene_descr = (t_descr *)malloc(sizeof(t_descr))))
		return (NULL);
	return (scene_descr);
}

void	get_resolution(char *line, t_descr **scene_descr)
{
	line++;
		(*scene_descr)->resolution_x = ft_atoi(line);
	while (('0' <= *line && *line <= '9') || *line == '-')
		line++;
	(*scene_descr)->resolution_y = ft_atoi(line);
}

char	*get_color(char *line)
{
	int 	i;
	int 	q;
	int 	flag;
	char 	*result;

	i = 0;
	if (!(result = (char*)malloc(3)))
		return (NULL);
	ft_memset(result, -1, 3);
	while (*line && i < 2)
	{
		if ((('0' <= *line && *line <= '9') || *line == '-') && flag)
		{
			q = ft_atoi(line);
			flag = 0;
			if (0 <= q && q <= 255)
				result = q;
		}
		else
			flag = 1;
		line++;
	}
	return (result);
}

int 	get_desrc(char *line, t_descr **scene_descr)
{
	int 	result;

	result = 1;
	if (line[0] == 'N' && line[1] == 'O')
		(*scene_descr)->textures[0] = ft_strdup(line + 3);
	else if (line[0] == 'S' && line[1] == 'O')
		(*scene_descr)->textures[1] = ft_strdup(line + 3);
	else if (line[0] == 'W' && line[1] == 'E')
		(*scene_descr)->textures[2] = ft_strdup(line + 3);
	else if (line[0] == 'E' && line[1] == 'A')
		(*scene_descr)->textures[3] = ft_strdup(line + 3);
	else if (*line == 'S')
		(*scene_descr)->sprite_texture = ft_strdup(line + 2);
	else if (*line == 'R')
		 get_resolution(line, scene_descr);
	else if (*line == 'F')
		(*scene_descr)->floor_color = get_color(line);
	else if (*line == 'C')
		(*scene_descr)->celling_color = get_color(line);
	else
		result = 0;
	free(line);
	return (result);
}

char	*get_map(int fd)
{
	char	*line;
	char	*map;
	char 	*temp_line;
	char	*temp_map;

	while (get_next_line(fd, &line) > 0)
	{
		ft_realloc(map, ft_strlen(line));
		temp_line = line;
		while (*line)
		{
			if (*line == ' ' || *line == '0' || *line == '1' || *line == '2' ||
				*line == 'N' || *line == 'S' || *line == 'E' || *line == 'W')
				*map++ = *line++;
			else
			{
				free(temp_map);
				return (NULL);
			}
		}
		free(temp_line);
	}
	return (temp_map);
}

int main(int ac, char **av)
{
	char		*line;
	t_descr		*scene_descr;
	int			count_arg;
	const int	fd = open(av[1], O_RDONLY);

	if (ac != 2)
		return((int)write(1, "ERROR", 5) - 5 );
	count_arg = 0;
	scene_descr = create_struct();
	while (count_arg < 6)
	{
		get_next_line(fd, &line);
		count_arg += get_desrc(line, &scene_descr);
	}
	if ((scene_descr->map = get_map(fd)) == NULL)
		return((int)write(1, "ERROR", 5) - 5 );
	return (0);
}
