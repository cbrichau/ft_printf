/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_extraction.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrichau <cbrichau@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 16:12:37 by cbrichau          #+#    #+#             */
/*   Updated: 2019/07/21 14:47:08 by cbrichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** FT_GET_EXTRACTION_TYPE
** Defines cv.is_char_int_double by returning:
** [0] = none --> p
** [1] = char(*) --> cs, diouxX +hh
** [2] = int --> diouxX DOU
** [3] = double --> fF
*/

int		ft_get_extraction_type(t_conv *cv)
{
	if (ft_c_in_str(cv->spec, "cs"))
		return (1);
	if (ft_c_in_str(cv->spec, "diouxXDOU"))
	{
		if (ft_c_in_str(cv->spec, "diouxX") && ft_strcmp(cv->length, "hh") == 0)
			return (1);
		return (2);
	}
	if (ft_c_in_str(cv->spec, "fF"))
		return (3);
	return (0);
}

/*
** FT_GET_EXTRACTION_SIZE
** Defines cv.is_sh_lg_lg_m_s by returning:
** [0] = no length
** [1] = short --> diouxX +h
** [2] = long --> diouxX +l, fF +L, DOU
** [3] = long long --> diouxX +ll
** [4] = intmax_t / uintmax_t --> diouxX +j
** [5] = size_t / ssize_t --> diouxX +z
*/

int		ft_get_extraction_size(t_conv *cv)
{
	if (ft_c_in_str(cv->spec, "DOU"))
		return (2);
	if (cv->length[0] != '\0')
	{
		if (ft_c_in_str(cv->spec, "diouxX"))
		{
			if (ft_strcmp(cv->length, "h") == 0)
				return (1);
			else if (ft_strcmp(cv->length, "l") == 0)
				return (2);
			else if (ft_strcmp(cv->length, "ll") == 0)
				return (3);
			else if (ft_strcmp(cv->length, "j") == 0)
				return (4);
			else if (ft_strcmp(cv->length, "z") == 0)
				return (5);
		}
		if (ft_c_in_str(cv->spec, "fF") && ft_strcmp(cv->length, "L") == 0)
			return (2);
	}
	return (0);
}

/*
** FT_GET_EXTRACTION_UNSIGNED
** Defines cv.is_unsigned by returning:
** [0] = signed --> default
** [1] = unsigned --> ouxX OU
*/

int		ft_get_extraction_unsigned(t_conv *cv)
{
	if (ft_c_in_str(cv->spec, "ouxXOU"))
		return (1);
	return (0);
}

/*
** FT_GET_EXTRACTION_BASE
** Defines cv.base by returning:
** [8] --> oO
** [16] --> xX
** [10] --> defauft
*/

int		ft_get_extraction_base(t_conv *cv)
{
	if (cv->spec == 'b')
		return (2);
	if (cv->spec == 'o' || cv->spec == 'O')
		return (8);
	else if (cv->spec == 'x' || cv->spec == 'X')
		return (16);
	else
		return (10);
}

/*
** FT_CREATE_ARG_S_INVALID
** Defines arg_s in case there's actually no extraction (% or invalid spec).
*/

char	*ft_create_arg_s_invalid(char spec)
{
	char	*arg_s;

	if ((arg_s = ft_strnew(1)))
		arg_s[0] = spec;
	return (arg_s);
}
