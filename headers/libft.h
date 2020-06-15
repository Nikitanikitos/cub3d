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

int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isprint(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_atoi(const char *nptr);
int					ft_memcmp(const void *arr1, const void *arr2,
							size_t byte_sizes);
int					ft_strncmp(const char *arr1, const char *arr2,
							size_t byte_sizes);

size_t				ft_strlen(const char *str);
size_t				ft_strlcpy(char *dst, const char *src, size_t byte_sizes);
size_t				ft_strlcat(char *dst, const char *src, size_t byte_sizes);

void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int nbr, int fd);
void				ft_bzero(void *dest, size_t byte_sizes);
void				*ft_calloc(size_t num, size_t byte_sizes);
void 				*ft_realloc(char *src, int len);
void				*ft_memset(void *dest, int chr, size_t byte_sizes);
void				*ft_memchr(const void *arr, int c, size_t byte_sizes);
void				*ft_memcpy(void *dest, const void *src, size_t byte_sizes);
void				*ft_memmove(void *dest, const void *src, size_t byte_sizes);
void				*ft_memccpy(void *dest, const void *src, int c,
								size_t byte_sizes);

char				*ft_itoa(int n);
char				*ft_strdup(const char *src);
char				*ft_strcpy(char *dest, const char *src);
char				**ft_split(char const *s, char c);
//char				*ft_strchr(const char *str, int ch);
char				*ft_strrchr(const char *str, int ch);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(const char *s1, const char *s2);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char				*ft_strnstr(const char *big, const char *little,
								size_t len);


#endif
