/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 17:35:41 by imicah            #+#    #+#             */
/*   Updated: 2020/08/07 17:35:42 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *arr1, const char *arr2)
{
	if (arr1 == arr2)
		return (0);
	else if (arr1 == NULL)
		return (1);
	while (*arr1 == *arr2 && *arr2 && *arr1)
	{
		arr1++;
		arr2++;
	}
	return (*arr1 - *arr2);
}
