/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_big.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrichau <cbrichau@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 16:53:54 by cbrichau          #+#    #+#             */
/*   Updated: 2019/07/21 13:53:50 by cbrichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extra.h"

static int	ft_nb_len(uintmax_t nb, int is_neg)
{
	int	len;

	len = 0;
	if (is_neg)
		len++;
	if (nb == 0)
		len++;
	while (nb > 0)
	{
		len++;
		nb /= 10;
	}
	return (len);
}

char		*ft_itoa_big(uintmax_t nb, int is_neg)
{
	int		nb_len;
	char	*str;

	nb_len = ft_nb_len(nb, is_neg);
	if ((str = ft_strnew(nb_len)))
	{
		nb_len--;
		while (nb_len >= 0)
		{
			if (nb_len == 0 && is_neg)
				str[0] = '-';
			else
				str[nb_len] = nb % 10 + '0';
			nb /= 10;
			nb_len--;
		}
	}
	return (str);
}
