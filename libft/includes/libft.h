/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrichau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 15:59:35 by cbrichau          #+#    #+#             */
/*   Updated: 2019/07/21 14:01:14 by cbrichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

/*
** FT_MEM*
*/

void			*ft_memset(void *b, int c, size_t len);

/*
** FT_STR*
*/

char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t len);
char			*ft_strcat(char *restrict s1, const char *restrict s2);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strjoin(char const *s1, char const *s2);

/*
** FT_PUT*
*/

void			ft_putstr(char const *s);
void			ft_putstr_fd(char const *s, int fd);

/*
** Other
*/

void			ft_bzero(void *s, size_t n);
int				ft_atoi(const char *str);
char			*ft_itoa(int n);
int				ft_isdigit(int c);
#endif
