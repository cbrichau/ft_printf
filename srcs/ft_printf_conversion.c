/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conversion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrichau <cbrichau@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 16:46:41 by cbrichau          #+#    #+#             */
/*   Updated: 2019/07/30 17:09:48 by cbrichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** FT_CREATE_CV
** OUT: 'cv', the structure containing the conversion details.
** DOES:
**	1) Initialises some values of 'cv'.
**	2) Creates *fmt, a shorter string with only one set of conversion details.
**	3) Passes *fmt through 5 functions to extract the 5 conv params:
**	   %[flags][width][.precision][length]specifier.
** ---
** 3 > ft_printf_specifiers.c.
*/

t_conv		ft_create_cv(const char *restrict *format, va_list *ap)
{
	int		i;
	t_conv	cv;

	cv.valid_conversion = 1;
	ft_memset(cv.fmt, '\0', 100);
	ft_memset(cv.flags, '\0', 100);
	cv.width = 0;
	cv.precision = -1;
	ft_memset(cv.length, '\0', 3);
	cv.is_negative = 0;
	cv.conv_s = NULL;
	i = 0;
	while (!ft_c_in_str(format[0][i], VALID_SPEC) && format[0][i] != '\0' &&
			(ft_c_in_str(format[0][i], VALID_FLAGS) ||
			ft_c_in_str(format[0][i], VALID_LEN) ||
			ft_c_in_str(format[0][i], ".*") ||
			ft_isdigit(format[0][i])))
		i++;
	ft_strncpy(cv.fmt, format[0], i + 1);
	ft_get_flags(&cv);
	ft_get_width(&cv, ap);
	ft_get_precision(&cv, ap);
	ft_get_length(&cv);
	ft_get_specifier(&cv);
	return (cv);
}

/*
** FT_EXTRACT
** OUT: the argument extracted to *arg_s (NULL if malloc fails).
** DOES:
**	1) Calls 4 fcts to define the params/casting for the va_arg extraction:
**		- FT_GET_EXTRACTION_TYPE (p, char(*), int, double).
**		- FT_GET_EXTRACTION_SIZE (short, long, long*2, (u)intmax_t, (s)size_t).
**		- FT_GET_EXTRACTION_UNSIGNED (true/false).
**		- FT_GET_EXTRACTION_BASE (2, 8, 10, 16).
**	2) Creates *arg_s with:
**		- FT_CREATE_ARG_S_INVALID if the specifier is not valid (empty *arg_s).
**		- FT_EXTRACT_PTR, _CHAR, _INT/UINT, _DOUBLE, depending in the type.
** ---
** 1.abcd, 2a > ft_printf_extraction.c.
** 2.bcdef > ft_printf_extraction2.c.
*/

char		*ft_extract(t_conv *cv, va_list *ap)
{
	char	*arg_s;

	cv->is_char_int_double = ft_get_extraction_type(cv);
	cv->is_sh_lg_lg_m_s = ft_get_extraction_size(cv);
	cv->is_unsigned = ft_get_extraction_unsigned(cv);
	cv->base = ft_get_extraction_base(cv);
	if (cv->spec == '%' || !ft_c_in_str(cv->spec, VALID_SPEC))
		arg_s = ft_create_arg_s_invalid(cv->spec);
	else if (cv->spec == 'p')
		arg_s = ft_extract_ptr(ap);
	else if (cv->is_char_int_double == 1)
		arg_s = ft_extract_char(ap, cv);
	else if (cv->is_char_int_double == 2)
	{
		if (!cv->is_unsigned)
			arg_s = ft_extract_int(ap, cv);
		else
			arg_s = ft_extract_uint(ap, cv);
	}
	else if (cv->is_char_int_double == 3)
		arg_s = ft_extract_double(ap, cv);
	else
		arg_s = NULL;
	return (arg_s);
}

/*
** FT_CONVERT
** OUT: the argument converted and saved to cv.conv_s (NULL if malloc fails).
** DOES:
**	1) Calls FT_INITIALISE_CONV_S:
**		- Initialises *conv_s large enough to hold
**			*arg_s and all its (potential) upcoming conversions. So len =
**			+ length of arg_s (= minimun basic space required).
**			+ 2 (= added padding for p).
**			+ 3 (= max extra flags conversion: 2 for #, 1 for ' '/+).
**			+ cv.width (= max extra required for width conversion).
**			+ cv.precision (= max extra required for precision conversion).
**		- Prefills *conv_s with the content of *arg_s.
**		- Frees *arg_s that is no longer needed.
**	2) Calls conversion functions as needed, updating *conv_s in each:
**		- FT_CONVERT_PRECISION
**		- FT_CONVERT_FLAGS
**		- FT_CONVERT_WIDTH
** ---
** 2.abc > ft_printf_conversion2.c
*/

static char	*ft_initialise_conv_s(t_conv *cv, char *arg_s)
{
	int	len;

	len = ft_strlen(arg_s) + 2 + 3 + cv->width;
	if (cv->precision > 0)
		len += cv->precision;
	if ((cv->conv_s = ft_strnew(len)))
		ft_strcpy(cv->conv_s, arg_s);
	ft_strdel(&arg_s);
	return (cv->conv_s);
}

char		*ft_convert(t_conv *cv, char *arg_s)
{
	if (!(cv->conv_s = ft_initialise_conv_s(cv, arg_s)))
		return (NULL);
	ft_convert_precision(cv);
	ft_convert_flags(cv);
	ft_convert_width(cv);
	if (ft_c_in_str(cv->spec, "px"))
		cv->conv_s = ft_convert_case(cv->conv_s);
	return (cv->conv_s);
}
