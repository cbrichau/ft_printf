/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtoa_in_range.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrichau <cbrichau@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 17:54:46 by cbrichau          #+#    #+#             */
/*   Updated: 2019/07/27 17:05:36 by cbrichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extra.h"

/*
** Support functions:
**	- FT_DEFINE_PART_INT:
**		Takes the int part (e.g. 5) from the original value (e.g. 5.012).
**		Saves it in 'part_int' + defines 'is_neg'.
**	- FT_DEFINE_PART_DEC:
**		Takes the dec part (0.012) from the original value.
**		Adds 1 to keep leading 0s and notice rounding. Multiplies by 10
**		precision times to save as int (e.g. 0.012 * 10 * 10).
**		Saves it rounded in 'part_dec'.
**	- FT_CONVERT_PARTS_TO_STR:
**		Convert 'part_dec/int' to 'str_dec/int' and gets the len of both.
**		If str_dec doesn't start with 1, it was rounded into 'part_int' which
**		has to be incremented before converting.
**	- FT_CREATE_STR
**		Combines "(-) str_int (. str_dec)" into a single string.
*/

static void	ft_define_part_int(t_float_nb *nb)
{
	if (nb->value < 0)
	{
		nb->part_int = (uintmax_t)-nb->value;
		nb->is_neg = 1;
	}
	else
	{
		nb->part_int = (uintmax_t)nb->value;
		nb->is_neg = 0;
	}
}

static void	ft_define_part_dec(t_float_nb *nb)
{
	long double	buf;
	int			i;

	if (nb->value >= 0)
		buf = nb->value - nb->part_int + 1;
	else
		buf = nb->value + nb->part_int - 1;
	i = 0;
	while (i < nb->precision)
	{
		buf *= 10;
		i++;
	}
	if (buf > 0)
		nb->part_dec = (uintmax_t)(buf + 0.5);
	else
		nb->part_dec = (uintmax_t)(-buf + 0.5);
}

static int	ft_convert_parts_to_str(t_float_nb *nb)
{
	if ((nb->str_dec = ft_itoa_big(nb->part_dec, 0)))
	{
		if (nb->str_dec[0] != '1')
			nb->part_int++;
		if ((nb->str_int = ft_itoa_big(nb->part_int, nb->is_neg)))
		{
			nb->len_int = ft_strlen(nb->str_int);
			nb->len_dec = ft_strlen(nb->str_dec);
			return (1);
		}
		ft_strdel(&nb->str_dec);
	}
	return (-1);
}

static void	ft_create_str(t_float_nb *nb, char *str)
{
	int		i;
	int		j;

	i = 0;
	while (i < nb->len_int)
	{
		str[i] = nb->str_int[i];
		i++;
	}
	if (nb->precision > 0)
	{
		str[i] = '.';
		i++;
		j = 1;
		while (j <= nb->len_dec)
		{
			str[i] = nb->str_dec[j];
			i++;
			j++;
		}
	}
}

/*
** FT_DTOA_IN_RANGE
** Used to convert doubles that fit in the INT_MIN/MAX range.
**	1) Initialises the value & precision (given).
**	2) Calls FT_DEFINE_PART_INT to extract the int part of the double.
**	3) Calls FT_DEFINE_PART_DEC to extract the decimal part.
**	4) Calls FT_CONVERT_PARTS_TO_STR to convert bot parts to strings.
**	5) Calls FT_CREATE_STR to unite both strings into a single, the result.
*/

char		*ft_dtoa_in_range(long double n, int precision)
{
	t_float_nb	nb;
	char		*str;

	nb.value = n;
	nb.precision = precision;
	ft_define_part_int(&nb);
	ft_define_part_dec(&nb);
	if ((ft_convert_parts_to_str(&nb)))
	{
		if ((str = ft_strnew(nb.len_int + nb.len_dec)))
			ft_create_str(&nb, str);
		ft_strdel(&nb.str_int);
		ft_strdel(&nb.str_dec);
		return (str);
	}
	return (NULL);
}
