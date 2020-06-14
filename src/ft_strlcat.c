/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 16:35:38 by imicah            #+#    #+#             */
/*   Updated: 2020/05/03 01:49:25 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t byte_sizes)
{
	size_t			result;
	size_t const	len_dst = ft_strlen(dst);
	size_t const	len_src = ft_strlen(src);

	result = len_src + len_dst;
	if (byte_sizes <= len_dst)
		return (len_src + byte_sizes);
	while (*dst)
		dst++;
	byte_sizes = byte_sizes - len_dst - 1;
	while (byte_sizes-- && *src)
		*(dst++) = *(src++);
	*dst = '\0';
	return (result);
}
