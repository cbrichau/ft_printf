/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conversion2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrichau <cbrichau@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 16:46:32 by cbrichau          #+#    #+#             */
/*   Updated: 2019/08/02 12:02:13 by cbrichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** FT_CONVERT_PRECISION
** OUT: / (updates cv->conv_s).
** DOES:
**	Depends on precision, specifier & input value:
**	- Precision = 0:
**		(p=0X0 / diouxXDOU=0): Removes 0 and prints 0X/nothing.
**	- Precision > len str (not counting leading '-' or '0X'):
**		(pdiouxXDOU): Adds leading 0s according to precision.
**	- Precision >= 0 and < len str:
**		(s): Truncates *s so its length equals the precision.
*/

static void	ft_set_precision_padding(t_conv *cv, int len_pad)
{
	char	padding[100];

	ft_memset(padding, '\0', 100);
	ft_memset(padding, '0', len_pad);
	if (cv->is_negative)
		cv->conv_s[0] = '0';
	else if (cv->spec == 'p')
		cv->conv_s[1] = '0';
	cv->conv_s = ft_strcat_reversed(cv->conv_s, padding);
	if (cv->is_negative)
		cv->conv_s[0] = '-';
	else if (cv->spec == 'p')
		cv->conv_s[1] = 'X';
}

void		ft_convert_precision(t_conv *cv)
{
	int	len_str;

	if (cv->precision == -1 || ft_c_in_str(cv->spec, "fF"))
		return ;
	len_str = ft_strlen(cv->conv_s);
	if (cv->precision == 0 && ft_c_in_str(cv->spec, "pdiouxXDOU"))
	{
		if (cv->spec == 'p' && ft_strcmp(cv->conv_s, "0X0") == 0)
			ft_memset_start(cv->conv_s, '\0', 2, len_str);
		else if (ft_strcmp(cv->conv_s, "0") == 0)
			ft_memset(cv->conv_s, '\0', len_str);
	}
	else if (cv->precision + 2 > len_str && cv->spec == 'p')
		ft_set_precision_padding(cv, cv->precision + 2 - len_str);
	else if (cv->precision + cv->is_negative > len_str
			&& ft_c_in_str(cv->spec, "diouxXDOU"))
		ft_set_precision_padding(cv, cv->precision + cv->is_negative - len_str);
	else if (cv->precision >= 0 && cv->precision < len_str && cv->spec == 's')
		ft_memset_start(cv->conv_s, '\0', cv->precision, len_str);
}

/*
** FT_CONVERT_FLAGS
** OUT: / (updates cv->conv_s).
** DOES:
**	Depends on flag & specifier:
**	'#'
**  	(oO/xX): Increases precision to precede the number with 0 / 0x,0X
**				 unless the value already |starts with / equals| 0.
**		(fF): Includes a decimal point despite no decimal part.
**	' '
**		(dDifF): Adds a blank on the left of a positive number.
**	'+'
**		(difDF): A sign is always placed before a number (overrides ' ').
**	'0': applied in width padding.
**	'-': applied in width padding.
**	'*': applied in width/precision extraction.
*/

void		ft_convert_flags(t_conv *cv)
{
	int	last_c;

	if (cv->flags[0] == '\0')
		return ;
	if (ft_c_in_str('#', cv->flags))
	{
		last_c = ft_strlen(cv->conv_s) - 1;
		if (ft_c_in_str(cv->spec, "oO") && cv->conv_s[0] != '0')
			cv->conv_s = ft_strcat_reversed(cv->conv_s, "0");
		else if (ft_c_in_str(cv->spec, "xX") && cv->conv_s[0] != '\0' &&
				!(cv->conv_s[0] == '0' && cv->conv_s[last_c] == '0'))
			cv->conv_s = ft_strcat_reversed(cv->conv_s, "0X");
		else if (ft_c_in_str(cv->spec, "fF") && !ft_c_in_str('.', cv->conv_s))
			cv->conv_s[last_c + 1] = '.';
	}
	if (ft_c_in_str(cv->spec, "difDF") && !cv->is_negative)
	{
		if (ft_c_in_str(' ', cv->flags))
			cv->conv_s = ft_strcat_reversed(cv->conv_s, " ");
		else if (ft_c_in_str('+', cv->flags))
			cv->conv_s = ft_strcat_reversed(cv->conv_s, "+");
	}
}

/*
** FT_CONVERT_WIDTH
** OUT: / (updates cv->conv_s).
** DOES:
**	Default behaviour: if width > len_str, adds [left ' '] padding.
**	Modified by specifier:
**		'c':
**	Modified by flags:
**		'-': [right] padding.
**		'0': ['0'] padding. Ignored for int with pecision defined.
** The following flags can modify this:
**  0 (all; ignored for int with precision defined) -> Width adding uses '0'.
**  - (all) -> Width adding is on the right with ' ' (overrides 0).
*/

static void	ft_set_width_padding(t_conv *cv, t_pad *padding)
{
	int		ref;
	char	sign;

	ref = -1;
	if (padding->character == '0' && padding->side == 'l')
	{
		if (ft_c_in_str(cv->conv_s[0], "-+ "))
			ref = 0;
		else if (cv->conv_s[0] == '0' && cv->conv_s[1] == 'X')
			ref = 1;
		if (ref != -1)
		{
			sign = cv->conv_s[ref];
			cv->conv_s[ref] = '0';
		}
	}
	if (padding->side == 'l')
		cv->conv_s = ft_strcat_reversed(cv->conv_s, padding->str);
	else
		cv->conv_s = ft_strcat(cv->conv_s, padding->str);
	if (ref != -1)
		cv->conv_s[ref] = sign;
}

void		ft_convert_width(t_conv *cv)
{
	int		len_str;
	t_pad	padding;

	if (cv->width == 0)
		return ;
	len_str = ft_strlen(cv->conv_s);
	padding.len = cv->width - len_str;
	if (cv->spec == 'c' && len_str == 0)
		padding.len = cv->width - 1;
	if (padding.len > 0)
	{
		padding.side = 'l';
		if (ft_c_in_str('-', cv->flags))
			padding.side = 'r';
		padding.character = ' ';
		if (ft_c_in_str('0', cv->flags) &&
			!(ft_c_in_str(cv->spec, "pdiouxXDOU") && cv->precision > -1))
			padding.character = '0';
		ft_memset(padding.str, '\0', 100);
		ft_memset(padding.str, padding.character, padding.len);
		ft_set_width_padding(cv, &padding);
	}
}
