/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 01:31:15 by imicah            #+#    #+#             */
/*   Updated: 2020/05/02 12:53:16 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strchr(const char *src, char c)
{
	const char *src_copy = src;

	while (*src_copy)
		if (*src_copy++ == c)
			return ((int)(src_copy - src));
	if (c == '\0')
		return ((int)(src_copy - src));
	return (0);
}
