/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_specifiers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrichau <cbrichau@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 15:31:57 by cbrichau          #+#    #+#             */
/*   Updated: 2019/07/30 17:24:23 by cbrichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** 1) FT_GET_FLAGS
** OUT: / (updates cv->flags).
** DOES:
**	Defines cv.flags to a string of unique instructions (empty if none).
**	Uses FT_CLEAN_FLAGS (ft_printf_flags_extra.c) for overrides/duplicates.
** --
** Incl basic: # 0 - + space
** Incl bonus: * (in width & precision)
*/

void	ft_get_flags(t_conv *cv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cv->fmt[i] != '\0')
	{
		if (ft_c_in_str(cv->fmt[i], VALID_FLAGS))
		{
			if (!(cv->fmt[i] == '0' && i > 0 &&
				(ft_isdigit(cv->fmt[i - 1]) || cv->fmt[i - 1] == '.')))
			{
				cv->flags[j] = cv->fmt[i];
				j++;
			}
		}
		i++;
	}
	ft_clean_flags(cv);
}

/*
** 2) FT_GET_WIDTH
** OUT: / (updates cv->width).
** DOES:
**	Defines cv.width to a number >= 0 (0 if none).
**	Uses FT_ADD_FLAG (ft_printf_flags_extra.c) to add '-' from '*'.
** --
** Incl basic: positive int
** Incl bonus: * with pos/neg int
*/

void	ft_get_width(t_conv *cv, va_list *ap)
{
	int	i;

	i = 0;
	while (cv->fmt[i] != '\0')
	{
		if (ft_c_in_str(cv->fmt[i], "*123456789") && !(i > 0 &&
		((cv->fmt[i - 1] == '.') || ft_c_in_str(cv->fmt[i - 1], "123456789"))))
		{
			if (cv->fmt[i] == '*')
			{
				cv->width = va_arg(*ap, int);
				i++;
				if (cv->width < 0)
				{
					cv->width *= -1;
					ft_add_flag("-", cv);
				}
			}
			if (ft_isdigit(cv->fmt[i]))
				cv->width = ft_atoi(&cv->fmt[i]);
			return ;
		}
		i++;
	}
}

/*
** 3) FT_GET_PRECISION
** OUT: / (updates cv->precision).
** DOES: Defines cv.precision to a number >= 0 (if none, if f: 6, else: -1).
** --
** Incl basic: pos/neg int
** Incl bonus: * with pos/neg int
*/

void	ft_get_precision(t_conv *cv, va_list *ap)
{
	int	i;

	i = 0;
	while (cv->fmt[i] != '\0' &&
		!(cv->fmt[i] == '.' && ft_c_in_str(cv->fmt[i + 1], "*-0123456789")))
		i++;
	if (cv->fmt[i] == '.')
	{
		i++;
		if (cv->fmt[i] == '*')
			cv->precision = va_arg(*ap, int);
		else if (cv->fmt[i] == '-' && ft_isdigit(cv->fmt[i + 1]))
		{
			cv->width = ft_atoi(&cv->fmt[i + 1]);
			cv->precision = 0;
		}
		else if (ft_isdigit(cv->fmt[i]))
			cv->precision = ft_atoi(&cv->fmt[i]);
	}
	else if (ft_c_in_str('.', cv->fmt))
		cv->precision = 0;
	else if (ft_c_in_str('f', cv->fmt) || ft_c_in_str('F', cv->fmt))
		cv->precision = 6;
}

/*
** 4) FT_GET_LENGTH
** OUT: / (updates cv->length).
** DOES: Defines cv.length to a 1/2-letter string (empty if no [valid] length).
** --
** Incl basic: h hh l ll L
** Incl bonus: j z
*/

void	ft_get_length(t_conv *cv)
{
	int	i;

	i = 0;
	while (cv->fmt[i] != '\0' && !ft_c_in_str(cv->fmt[i], VALID_LEN))
		i++;
	if (ft_c_in_str(cv->fmt[i], VALID_LEN))
	{
		if (ft_c_in_str(cv->fmt[i], "hl") && cv->fmt[i] == cv->fmt[i + 1])
		{
			cv->length[0] = cv->fmt[i];
			cv->length[1] = cv->fmt[i + 1];
		}
		else
			cv->length[0] = cv->fmt[i];
	}
}

/*
** 5) FT_GET_SPECIFIER
** OUT: / (updates cv->length).
** DOES: Defines cv.spec according to the last char of cv.fmt
**		(whether it's a VALID_SPEC or not).
** --
** Incl basic: csp diouxX f %
** Incl bonus: DOU F b
*/

void	ft_get_specifier(t_conv *cv)
{
	int	i;

	i = 0;
	while (cv->fmt[i] != '\0')
		i++;
	i--;
	if (ft_c_in_str(cv->fmt[i], VALID_SPEC))
		cv->spec = cv->fmt[i];
	else if (!ft_c_in_str(cv->fmt[i], VALID_LEN) && cv->fmt[i] != ' ')
		cv->spec = cv->fmt[i];
	else
		cv->spec = '\0';
}
