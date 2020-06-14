/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 18:56:22 by imicah            #+#    #+#             */
/*   Updated: 2020/05/11 13:18:32 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putnbr_fd(int nbr, int fd)
{
	char		c;
	long int	l_nbr;

	l_nbr = nbr;
	if (l_nbr < 0)
	{
		write(fd, "-", 1);
		l_nbr *= -1;
	}
	if (l_nbr > 9)
		ft_putnbr_fd(l_nbr / 10, fd);
	c = l_nbr % 10 + '0';
	write(fd, &c, 1);
}
