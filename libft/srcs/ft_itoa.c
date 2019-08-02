/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrichau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:30:27 by cbrichau          #+#    #+#             */
/*   Updated: 2019/04/25 16:52:16 by cbrichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_nb_len(long int nb, int nb_len)
{
	while (nb > 0)
	{
		nb /= 10;
		nb_len++;
	}
	return (nb_len);
}

char				*ft_itoa(int n)
{
	long int	nb;
	int			nb_len;
	char		*str;

	nb = n;
	nb_len = 0;
	if (n < 0)
		nb *= -1;
	if (n <= 0)
		nb_len = 1;
	nb_len = ft_nb_len(nb, nb_len);
	if (!(str = ft_strnew(nb_len)))
		return (NULL);
	while ((nb / 10) > 0)
	{
		nb_len--;
		str[nb_len] = nb % 10 + '0';
		nb /= 10;
	}
	nb_len--;
	str[nb_len] = nb + '0';
	if (n < 0)
		str[0] = '-';
	return (str);
}
