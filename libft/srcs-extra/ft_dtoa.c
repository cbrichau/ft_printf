/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrichau <cbrichau@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 20:24:24 by cbrichau          #+#    #+#             */
/*   Updated: 2019/07/27 17:05:47 by cbrichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extra.h"

static void	ft_free_strings(t_big_float_nb *nb, int pone, int ptwo, int res)
{
	if (pone == 1 && nb->result_part_one)
		ft_strdel(&nb->result_part_one);
	if (ptwo == 1 && nb->result_part_two)
		ft_strdel(&nb->result_part_two);
	if (res == 1)
		ft_strdel(&nb->result);
}

/*
** divides the double by 10.000.000 until it fits int uintmax_t
** converts that leading part into a str with itoa_big
** joins it to the result we already have
** return the nb of divisions made
*/

static void	ft_add_start_int_to_result(t_big_float_nb *nb)
{
	long double	n;

	n = nb->value;
	nb->divisions = 0;
	while (n > INT_MAX || n < INT_MIN)
	{
		n /= 10000000;
		nb->divisions++;
	}
	nb->start_int = (uintmax_t)n;
	nb->result_part_one = ft_strdup(nb->result);
	nb->result_part_two = ft_itoa_big(nb->start_int, nb->is_neg);
	nb->is_neg = 0;
	ft_free_strings(nb, 0, 0, 1);
	if (nb->result_part_one && nb->result_part_two)
		nb->result = ft_strjoin(nb->result_part_one, nb->result_part_two);
	else
		nb->divisions = 0;
	ft_free_strings(nb, 1, 1, 0);
}

static void	ft_remove_start_int_from_double(t_big_float_nb *nb)
{
	long double	start_double;

	start_double = (long double)nb->start_int;
	while (nb->divisions > 0)
	{
		start_double *= 10000000;
		nb->divisions--;
	}
	nb->value -= start_double;
}

/*
** xx
*/

static char	*ft_decompose_part_int(t_big_float_nb *nb)
{
	if (!(nb->result = ft_strnew(0)))
		return (NULL);
	while (nb->value > INT_MAX || nb->value < INT_MIN)
	{
		ft_add_start_int_to_result(nb);
		if (nb->divisions == 0)
			return (NULL);
		ft_remove_start_int_from_double(nb);
	}
	nb->result_part_one = ft_strdup(nb->result);
	ft_free_strings(nb, 0, 0, 1);
	return (nb->result_part_one);
}

/*
** xx
*/

char		*ft_dtoa(long double n, int precision)
{
	t_big_float_nb	nb;

	if (n > INT_MAX || n < INT_MIN)
	{
		nb.value = n;
		nb.is_neg = 0;
		if (n < 0)
		{
			nb.value = -n;
			nb.is_neg = 1;
		}
		nb.result_part_one = ft_decompose_part_int(&nb);
		nb.result_part_two = ft_dtoa_in_range(nb.value, precision);
		if (nb.result_part_one && nb.result_part_two)
			nb.result = ft_strjoin(nb.result_part_one, nb.result_part_two);
		ft_free_strings(&nb, 1, 1, 0);
		return (nb.result);
	}
	return (ft_dtoa_in_range(n, precision));
}
