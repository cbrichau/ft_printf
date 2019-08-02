/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binary_to_base_8_16.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrichau <cbrichau@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 13:32:04 by cbrichau          #+#    #+#             */
/*   Updated: 2019/07/21 13:51:52 by cbrichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extra.h"

/*
** FT_BINARY_TO_BASE_8_16
** OUT: the given binary in octal/hex base saved in a *s (NULL if malloc fails).
** DOES:
**	1) FT_INITIALISE_STRUCTURE:
**		Sets the char*s to empty \0, then fills the first nibble (000 / 0000),
**		and the base_table (01234567 / 0123456789ABCDEF).
**	2) FT_CREATE_CONVERSION_TABLE:
**		Creates a 2D table where each element of base_table matches a nibble.
**		The first nibble is given, the successively increased (001, 010, 011, ).
**	3) FT_CONVERT:
**		Reads *binary from the end, using FT_EXTRACT_NIBBLE to exctract one
**		nibble at a time, then looking for its match in the conversion_table,
**		finally saving its corresponding octal/hex value in *result.
*/

static void	ft_initialise_structure(t_bin_conv *cv)
{
	int	i;

	ft_memset(cv->nibble, '\0', 5);
	ft_memset(cv->base_table, '\0', 17);
	i = 0;
	while (i < 16)
	{
		ft_memset(cv->conversion_table[i], '\0', 5);
		i++;
	}
	cv->n_size = 4;
	if (cv->base == 8)
		cv->n_size = 3;
	ft_memset(cv->nibble, '0', cv->n_size);
	i = 0;
	while (i < cv->base)
	{
		if (i < 10)
			cv->base_table[i] = '0' + i;
		else
			cv->base_table[i] = 'A' + i - 10;
		i++;
	}
}

static void	ft_create_conversion_table(t_bin_conv *cv)
{
	int		i;
	int		j;

	i = 0;
	while (i < cv->base)
	{
		if (i != 0)
		{
			j = cv->n_size - 1;
			while (cv->nibble[j] != '0')
			{
				cv->nibble[j] = '0';
				j--;
			}
			cv->nibble[j] = '1';
		}
		ft_strcpy(cv->conversion_table[i], cv->nibble);
		i++;
	}
}

static void	ft_extract_nibble(char *binary, t_bin_conv *cv, int *pos)
{
	int	i;

	i = cv->n_size - 1;
	while (i >= 0)
	{
		(*pos)--;
		if (*pos >= 0)
			cv->nibble[i] = binary[*pos];
		else
			cv->nibble[i] = '0';
		i--;
	}
}

static char	*ft_convert(char *binary, t_bin_conv *cv)
{
	int		i;
	int		binary_len;
	int		result_len;
	char	*result;

	binary_len = ft_strlen(binary);
	result_len = binary_len / cv->n_size;
	if ((binary_len % cv->n_size) != 0)
		result_len += 1;
	if ((result = ft_strnew(result_len)))
	{
		while (result_len > 0)
		{
			result_len--;
			ft_extract_nibble(binary, cv, &binary_len);
			i = 0;
			while (ft_strcmp(cv->nibble, cv->conversion_table[i]) != 0)
				i++;
			result[result_len] = cv->base_table[i];
		}
	}
	return (result);
}

char		*ft_binary_to_base_8_16(char *binary, int base)
{
	t_bin_conv	cv;

	cv.base = base;
	ft_initialise_structure(&cv);
	ft_create_conversion_table(&cv);
	return (ft_convert(binary, &cv));
}
