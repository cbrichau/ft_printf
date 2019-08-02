/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decimal_to_binary.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrichau <cbrichau@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 14:16:19 by cbrichau          #+#    #+#             */
/*   Updated: 2019/07/21 13:53:09 by cbrichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extra.h"

static int	ft_get_binary_len(uintmax_t nb, int is_neg)
{
	int	len;

	if (nb == 0)
		return (1);
	len = 0;
	while (nb > 0)
	{
		nb /= 2;
		len++;
	}
	if (is_neg)
	{
		len++;
		while (len != 16 && len != 32 && len != 64)
			len++;
	}
	return (len);
}

static void	ft_convert_positive(uintmax_t nb, int *len, char *binary)
{
	if (nb == 0)
	{
		(*len)--;
		binary[*len] = '0';
	}
	while (nb > 0)
	{
		(*len)--;
		binary[*len] = (nb % 2) + '0';
		nb /= 2;
	}
}

static void	ft_convert_negative(int len, char *binary)
{
	int	i;

	while (len >= 0)
	{
		len--;
		binary[len] = '0';
	}
	i = 0;
	while (binary[i] != '\0')
	{
		if (binary[i] == '1')
			binary[i] = '0';
		else
			binary[i] = '1';
		i++;
	}
	len = ft_strlen(binary) - 1;
	while (binary[len] != '0')
	{
		binary[len] = '0';
		len--;
	}
	binary[len] = '1';
}

/*
** Details -> instructables.com/id/Convert-Negative-Numbers-to-Binary
** Basically:
** 1) Convert +nb to binary the normal way (i.e. while nb/2 -> keep %2)
**    (= ft_convert_positive)
** 2) Extend the binary size to 16, 32 or 64 bytes, using '0' in extra space.
** 3) Switch all 0s to 1 and all 1s to 0.
** 4) And a single 1 at the end (1+1 = 10, so it goes up until it finds a 0).
**    (= ft_convert_negative)
** Knowing all this, we start by creating an empty *binary of the right size.
**    (= ft_get_binary_size)
*/

char		*ft_decimal_to_binary(uintmax_t nb, int is_neg)
{
	int		len;
	char	*binary;

	len = ft_get_binary_len(nb, is_neg);
	if ((binary = ft_strnew(len)))
	{
		ft_convert_positive(nb, &len, binary);
		if (is_neg)
			ft_convert_negative(len, binary);
	}
	return (binary);
}
