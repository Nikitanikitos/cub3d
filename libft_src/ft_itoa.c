/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 17:23:48 by imicah            #+#    #+#             */
/*   Updated: 2020/05/03 13:35:16 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_len(int n)
{
	size_t		i;
	long int	temp_n;

	i = 0;
	temp_n = n;
	if (n == 0)
		return (1);
	if (temp_n < 0)
	{
		temp_n = -temp_n;
		i++;
	}
	while (temp_n)
	{
		i++;
		temp_n /= 10;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	char		*result;
	size_t		i;
	long int	temp_n;

	i = ft_len(n);
	temp_n = n;
	if (!(result = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	result[i--] = '\0';
	if (temp_n == 0)
		result[i--] = '0';
	else if (temp_n < 0)
	{
		result[0] = '-';
		temp_n = -temp_n;
	}
	while (temp_n)
	{
		result[i--] = (temp_n % 10) + 48;
		temp_n /= 10;
	}
	return (result);
}
