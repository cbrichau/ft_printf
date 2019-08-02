/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrichau <cbrichau@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:42:50 by cbrichau          #+#    #+#             */
/*   Updated: 2019/08/02 17:56:04 by cbrichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** FT_PRINTF support functions:
**	- FT_PRINTF_FORMAT: Prints non-formatted text until % or \0 is found.
**						Increases *format and *len proportionnally.
**	- FT_PRINTF_ARGUMENT:
**	 1) Calls FT_CREATE_CV: Creates the structure with the conversion details.
**	 2) Calls FT_EXTRACTION: Extracts the content of *ap into *arg_s.
**	 3) Calls FT_CONVERT: Moves *arg_s to *conv_s.
**						  The applies the format changes to *conv_s.
**	 4) Calls FT_PRINT_CONVERSION_RESULT: Prints the output on screen.
** ---
** 1,2,3 > ft_printf_conversion.c
*/

static void	ft_print_conversion_result(t_conv *cv, int *len)
{
	ft_putstr(cv->conv_s);
	(*len) += ft_strlen(cv->conv_s);
	if (cv->spec == 'c' && (ft_strcmp(cv->conv_s, "\0") == 0 ||
		(cv->width > 0 && cv->conv_s[cv->width - 1] == '\0')))
	{
		write(1, "\0", 1);
		(*len)++;
	}
	ft_strdel(&cv->conv_s);
}

static int	ft_print_argument(const char *restrict *format,
								int *len, va_list *ap)
{
	t_conv	cv;
	char	*arg_s;

	cv = ft_create_cv(format, ap);
	(*format) += ft_strlen(cv.fmt);
	if (cv.spec == '\0')
		return (*len);
	if (!(arg_s = ft_extract(&cv, ap)))
	{
		va_end(*ap);
		return (*len);
	}
	if (arg_s[0] == '-')
		cv.is_negative = 1;
	if (!(cv.conv_s = ft_convert(&cv, arg_s)))
	{
		va_end(*ap);
		return (*len);
	}
	ft_print_conversion_result(&cv, len);
	return (-10);
}

static void	ft_print_format(const char *restrict *format, int *len)
{
	int	i;

	i = 0;
	while (format[0][i] != '%' && format[0][i] != '\0')
		i++;
	write(1, format[0], i);
	(*format) += i;
	(*len) += i;
}

/*
** ----------- Start of printf -----------
** FT_PRINTF
** Looks at *format char by char.
** 	- If not '%", calls FT_PRINTF_FORMAT to print all the text until % or \0.
** 	- If '%', calls FT_PRINTF_ARGUMENT to launch the whole process.
**	  When error, returns len and stops.
**	  When no error, returns 1 and goes to the next char.
*/

int			ft_printf(const char *restrict format, ...)
{
	int		len;
	int		ret;
	va_list	ap;

	len = 0;
	if (format)
	{
		va_start(ap, format);
		while (*format)
		{
			if (*format != '%')
				ft_print_format(&format, &len);
			else
			{
				format++;
				if ((ret = ft_print_argument(&format, &len, &ap)) != -10)
					return (ret);
			}
		}
		va_end(ap);
	}
	return (len);
}
