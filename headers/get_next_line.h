/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 17:48:33 by imicah            #+#    #+#             */
/*   Updated: 2020/05/17 12:39:02 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include "libft.h"

# define BUFFER_SIZE 32

int		get_next_line(int fd, char **line);
char	*ft_strndup(const char *src, int n);
void	add_list(register t_list **lst, char *buffer);
t_list	*ft_lstnew(void *content);

#endif
