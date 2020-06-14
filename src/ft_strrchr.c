/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 01:31:15 by imicah            #+#    #+#             */
/*   Updated: 2020/05/02 13:00:13 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	char	*temp_str;

	temp_str = NULL;
	while (*str)
	{
		if (*str == ch)
			temp_str = (char*)str;
		str++;
	}
	if (ch == '\0')
		temp_str = (char*)str;
	return (temp_str);
}
