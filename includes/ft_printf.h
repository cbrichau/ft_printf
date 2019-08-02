/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrichau <cbrichau@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 16:25:49 by cbrichau          #+#    #+#             */
/*   Updated: 2019/07/30 17:14:10 by cbrichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define VALID_SPEC "cspdiouxXf\%FDOU"
# define VALID_FLAGS "#0-+ "
# define VALID_LEN "hlLjz"
# include <stdarg.h>
# include "../libft/includes/libft_extra.h"

/*
** 1) ft_printf.c
** Reads the input and either prints it,
** or launches the conversion process.
*/

int				ft_printf(const char *restrict format, ...);

typedef struct	s_conv
{
	int		valid_conversion;
	char	fmt[100];
	char	flags[100];
	int		width;
	int		precision;
	char	length[3];
	char	spec;
	int		is_char_int_double;
	int		is_sh_lg_lg_m_s;
	int		is_unsigned;
	int		is_negative;
	int		base;
	char	*conv_s;
}				t_conv;

/*
** 2) ft_printf_conversion.c
** The conversion process consists of 3 steps:
** 	- 3) Create the conversion structure (cv).
**	- 4) Extract *ap (result stored in arg_s).
**	- 5) Convert *arg_s (result stored in cv.conv_s).
*/

t_conv			ft_create_cv(const char *restrict *format, va_list *ap);
char			*ft_extract(t_conv *cv, va_list *ap);
char			*ft_convert(t_conv *cv, char *arg_s);

/*
** 3a) ft_printf_specifiers.c
** Completes *cv by getting, from *format, the 5 conversion params
** (flags, width, precisio, length, specifier).
** Support fct for flags in ft_printf_flags_extra.c.
*/

void			ft_get_flags(t_conv *cv);
void			ft_get_width(t_conv *cv, va_list *ap);
void			ft_get_precision(t_conv *cv, va_list *ap);
void			ft_get_length(t_conv *cv);
void			ft_get_specifier(t_conv *cv);

void			ft_clean_flags(t_conv *cv);
void			ft_add_flag(char *newf, t_conv *cv);

/*
** 3b) ft_printf_extraction.c
** Further completes *cv by getting, from the specifier+length combinations,
** the 4 extraction params (data type, size, (un)signed, number base).
*/

int				ft_get_extraction_type(t_conv *cv);
int				ft_get_extraction_size(t_conv *cv);
int				ft_get_extraction_unsigned(t_conv *cv);
int				ft_get_extraction_base(t_conv *cv);

/*
** 4) ft_printf_extraction2.c (1st fct is in previous file actually)
** Based on extraction type, *ap is extracted
** through the appropriate extractor.
*/

char			*ft_create_arg_s_invalid(char spec);

char			*ft_extract_ptr(va_list *ap);
char			*ft_extract_char(va_list *ap, t_conv *cv);
char			*ft_extract_int(va_list *ap, t_conv *cv);
char			*ft_extract_uint(va_list *ap, t_conv *cv);
char			*ft_extract_double(va_list *ap, t_conv *cv);

/*
** 5) ft_printf_conversion2.c
** The extraction value stored in *arg_s is copied to *conv_s
** then converted by going through the relevant convertors.
*/

void			ft_convert_precision(t_conv *cv);
void			ft_convert_flags(t_conv *cv);
void			ft_convert_width(t_conv *cv);

typedef struct	s_pad
{
	int		len;
	char	side;
	char	character;
	char	str[100];
}				t_pad;
#endif
