/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrichau <cbrichau@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 16:16:05 by cbrichau          #+#    #+#             */
/*   Updated: 2019/07/21 14:49:25 by cbrichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extra.h"

/*
** https://www.rapidtables.com/convert/number/how-binary-to-decimal.html
*/

static char		*ft_binary_to_decimal(char *binary)
{
	int			len;
	int			exp;
	int			i;
	uintmax_t	nb;

	len = ft_strlen(binary) - 1;
	exp = 1;
	while (len > 0)
	{
		exp *= 2;
		len--;
	}
	nb = 0;
	i = 0;
	while (binary[i] != '\0')
	{
		if (binary[i] == '1')
			nb += exp;
		exp /= 2;
		i++;
	}
	return (ft_itoa_big(nb, 0));
}

static t_big_nb	ft_def_nb(intmax_t n, uintmax_t n2)
{
	t_big_nb	nb;

	if (n < 0)
	{
		nb.value = n * -1;
		nb.is_neg = 1;
		return (nb);
	}
	if (n > 0)
		nb.value = n;
	else
		nb.value = n2;
	nb.is_neg = 0;
	return (nb);
}

char			*ft_itoa_base(intmax_t n, uintmax_t n2,
							int base, int is_unsigned)
{
	t_big_nb	nb;
	char		*binary;
	char		*conv_s;

	nb = ft_def_nb(n, n2);
	if (nb.value == 0)
		return (ft_itoa(nb.value));
	if (base == 10 && !(nb.is_neg && is_unsigned))
		return (ft_itoa_big(nb.value, nb.is_neg));
	if ((binary = ft_decimal_to_binary(nb.value, nb.is_neg)))
	{
		if (base == 8 || base == 16)
			conv_s = ft_binary_to_base_8_16(binary, base);
		if (base == 10)
			conv_s = ft_binary_to_decimal(binary);
		ft_strdel(&binary);
		return (conv_s);
	}
	return (NULL);
}
