/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrichau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 11:52:55 by cbrichau          #+#    #+#             */
/*   Updated: 2019/04/25 16:24:39 by cbrichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len_s1;
	int		len_s2;
	int		i;
	char	*j_str;

	if (!(s1 && s2))
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (!(j_str = ft_strnew(len_s1 + len_s2)))
		return (NULL);
	i = 0;
	ft_strcat(j_str, s1);
	ft_strcat(j_str, s2);
	return (j_str);
}
