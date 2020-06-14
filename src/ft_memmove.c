/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 19:29:33 by imicah            #+#    #+#             */
/*   Updated: 2020/05/05 01:06:15 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dest, const void *src, size_t byte_sizes)
{
	char	*temp_dest;
	char	*temp_src;

	temp_dest = (char*)dest;
	temp_src = (char*)src;
	if (temp_dest == temp_src)
		return (dest);
	else if (temp_dest > temp_src)
		while (byte_sizes--)
			temp_dest[byte_sizes] = temp_src[byte_sizes];
	else
		while (byte_sizes--)
			*(temp_dest++) = *(temp_src++);
	return (dest);
}
