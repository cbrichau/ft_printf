/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrichau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:18:31 by cbrichau          #+#    #+#             */
/*   Updated: 2019/04/13 15:52:39 by cbrichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*b_ptr;

	i = 0;
	b_ptr = (unsigned char *)b;
	while (i < len)
	{
		b_ptr[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
