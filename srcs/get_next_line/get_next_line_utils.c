/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 18:56:20 by imicah            #+#    #+#             */
/*   Updated: 2020/05/12 18:56:22 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strndup(const char *src, int len)
{
	char	*result;
	size_t	i;

	i = 0;
	if (!(result = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (*src && len--)
		result[i++] = *(src++);
	result[i] = '\0';
	return (result);
}

void	add_list(t_list **lst, char *content)
{
	t_list	*temp;
	char	*prev_content;

	if (*lst == NULL)
	{
		*lst = ft_lstnew(content);
		return ;
	}
	temp = (*lst);
	while ((*lst)->next)
		*lst = (*lst)->next;
	if (ft_strchr((*lst)->content, '\n'))
		(*lst)->next = ft_lstnew(content);
	else
	{
		prev_content = (*lst)->content;
		(*lst)->content = ft_strjoin(prev_content, content);
		free(content);
		free(prev_content);
	}
	*lst = temp;
}
