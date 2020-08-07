/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 23:34:14 by imicah            #+#    #+#             */
/*   Updated: 2020/05/05 17:30:11 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_atoi(const char *nptr);
int					ft_strcmp(const char *arr1, const char *arr2);
int					ft_strchr(const char *str, char ch);

size_t				ft_strlen(const char *str);

void				ft_bzero(void *dest, size_t byte_sizes);
void				*ft_calloc(size_t num, size_t byte_sizes);
void				*ft_realloc(char *src, int len);

char				*ft_strdup(const char *src);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strjoin(char const *s1, char const *s2);

#endif
