/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 00:02:20 by imicah            #+#    #+#             */
/*   Updated: 2020/07/30 00:02:21 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

float		get_texture_coordinate(float current_x)
{
	if (current_x < 0)
		return (0);
	return (current_x);
}

float		get_distance(float x, float y)
{
	return (sqrtf(x * x + y * y));
}
