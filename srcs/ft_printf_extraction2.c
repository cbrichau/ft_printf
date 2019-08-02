/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_extraction2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrichau <cbrichau@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 16:45:27 by cbrichau          #+#    #+#             */
/*   Updated: 2019/07/18 17:28:29 by cbrichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** FT_EXTRACT_PTR
** Extracts 'p' input
*/

char		*ft_extract_ptr(va_list *ap)
{
	char	*p;
	char	*arg_s;

	p = ft_itoa_base(va_arg(*ap, long long int), 0, 16, 0);
	if (p)
	{
		arg_s = ft_strjoin("0X", p);
		ft_strdel(&p);
		return (arg_s);
	}
	return (NULL);
}

/*
** FT_EXTRACT_CHAR
** Extracts all char(*) combinations (c, s, diouxX +hh)
*/

char		*ft_extract_char(va_list *ap, t_conv *cv)
{
	char	*ext;
	char	*arg_s;
	int		i;

	if (cv->spec == 's')
	{
		if ((ext = va_arg(*ap, char *)))
			return ((arg_s = ft_strdup(ext)));
		else if (!(arg_s = ft_strnew(6)))
			return (NULL);
		return (ft_strcpy(arg_s, "(null)"));
	}
	else if (cv->spec == 'c')
	{
		if (!(arg_s = ft_strnew(1)))
			return (NULL);
		i = (int)(unsigned char)va_arg(*ap, int);
		arg_s[0] = (char)i;
		return (arg_s);
	}
	else if (!cv->is_unsigned)
		i = (int)(char)va_arg(*ap, int);
	else
		i = (int)(unsigned char)va_arg(*ap, unsigned int);
	return ((arg_s = ft_itoa_base(i, 0, cv->base, cv->is_unsigned)));
}

/*
** FT_EXTRACT_INT (Signed & Unsigned)
** Extracts all int combinations (diouxXb +h +l +ll +j +z, DOU)
*/

char		*ft_extract_int(va_list *ap, t_conv *cv)
{
	intmax_t	i;
	char		*arg_s;

	if (cv->is_sh_lg_lg_m_s == 1)
		i = (short int)va_arg(*ap, int);
	else if (cv->is_sh_lg_lg_m_s == 2)
		i = va_arg(*ap, long int);
	else if (cv->is_sh_lg_lg_m_s == 3)
		i = va_arg(*ap, long long int);
	else if (cv->is_sh_lg_lg_m_s == 4)
		i = va_arg(*ap, intmax_t);
	else if (cv->is_sh_lg_lg_m_s == 5)
		i = va_arg(*ap, size_t);
	else
		i = va_arg(*ap, int);
	arg_s = ft_itoa_base(i, 0, cv->base, 0);
	return (arg_s);
}

char		*ft_extract_uint(va_list *ap, t_conv *cv)
{
	uintmax_t	i;
	char		*arg_s;

	if (cv->is_sh_lg_lg_m_s == 1)
		i = (unsigned short int)va_arg(*ap, unsigned int);
	else if (cv->is_sh_lg_lg_m_s == 2)
		i = va_arg(*ap, unsigned long int);
	else if (cv->is_sh_lg_lg_m_s == 3)
		i = va_arg(*ap, unsigned long long int);
	else if (cv->is_sh_lg_lg_m_s == 4)
		i = va_arg(*ap, uintmax_t);
	else if (cv->is_sh_lg_lg_m_s == 5)
		i = va_arg(*ap, ssize_t);
	else
		i = va_arg(*ap, unsigned int);
	arg_s = ft_itoa_base(0, i, cv->base, 1);
	return (arg_s);
}

/*
** FT_EXTRACT_DOUBLE
** Extracts all double combinations (fF +L)
*/

char		*ft_extract_double(va_list *ap, t_conv *cv)
{
	long double	i;
	char		*arg_s;

	if (cv->is_sh_lg_lg_m_s == 2)
		i = va_arg(*ap, long double);
	else
		i = va_arg(*ap, double);
	arg_s = ft_dtoa(i, cv->precision);
	return (arg_s);
}
