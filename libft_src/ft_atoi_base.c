/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 04:45:43 by imicah            #+#    #+#             */
/*   Updated: 2020/06/29 04:45:44 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static char		ft_isspace(char c)
{
	return ((c == '\n' || c == '\t' || c == '\r' ||
			 c == '\v' || c == '\f' || c == ' '));
}

int	base(int c, int base)
{
	char *str = "0123456789abcdef";
	char *str2 = "0123456789ABCDEF";
	int  i = 0;

	while (i < base)
	{
		if (c == str[i] || c == str2[i])
			return (i);
		i++;
	}
	return (-1);
}

int ft_atoi_base(const char *str, int str_base)
{
	int nb;
	int negatif;

	nb = 0;
	negatif = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			negatif = -1;
		str++;
	}
	while (base(*str, str_base) != -1)
	{
		nb = nb * str_base;
		nb = nb + base(*str, str_base);
		str++;
	}
	return (nb * negatif);
}