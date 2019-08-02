/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrichau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:18:31 by cbrichau          #+#    #+#             */
/*   Updated: 2019/07/21 13:54:00 by cbrichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extra.h"

void	*ft_memset_start(void *b, int c, int start, size_t len)
{
	size_t			i;
	unsigned char	*b_ptr;

	i = start;
	b_ptr = (unsigned char *)b;
	while (i < len)
	{
		b_ptr[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
