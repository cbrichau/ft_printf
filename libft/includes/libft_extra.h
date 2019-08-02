/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft-entended.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrichau <cbrichau@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 14:06:17 by cbrichau          #+#    #+#             */
/*   Updated: 2019/07/27 17:08:09 by cbrichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_EXTRA_H
# define LIBFT_EXTRA_H
# define INT_MAX 2147483647
# define INT_MIN -2147483648
# include "libft.h"

/*
** VARIANTS OF LIBFT FUNCTIONS
*/

void			*ft_memset_start(void *b, int c, int start, size_t len);
char			*ft_strcat_reversed(char *s1, char *s2);

/*
** DATA TYPE CONVERSIONS
** (str->nb, nb->str, nb->nb, c->c)
*/

typedef struct	s_big_nb
{
	uintmax_t	value;
	int			is_neg;
}				t_big_nb;

char			*ft_itoa_base(intmax_t n, uintmax_t n2,
							int base, int is_unsigned);

typedef struct	s_float_nb
{
	long double	value;
	int			precision;
	int			is_neg;
	uintmax_t	part_int;
	uintmax_t	part_dec;
	char		*str_int;
	char		*str_dec;
	int			len_int;
	int			len_dec;
}				t_float_nb;

char			*ft_dtoa_in_range(long double n, int precision);

typedef struct	s_big_float_nb
{
	long double value;
	int			is_neg;
	uintmax_t	start_int;
	int			divisions;
	char		*result_part_one;
	char		*result_part_two;
	char		*result;
}				t_big_float_nb;

char			*ft_dtoa(long double n, int precision);

typedef struct	s_bin_conv
{
	int		base;
	int		n_size;
	char	nibble[5];
	char	base_table[17];
	char	conversion_table[16][5];
}				t_bin_conv;

char			*ft_binary_to_base_8_16(char *binary, int base);

char			*ft_itoa_big(uintmax_t nb, int is_neg);
char			*ft_decimal_to_binary(uintmax_t nb, int is_neg);
char			*ft_convert_case(char *s);

/*
** OTHER
*/

int				ft_c_in_str(char c, char *list);

#endif
