/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flags_extras.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrichau <cbrichau@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 17:27:25 by cbrichau          #+#    #+#             */
/*   Updated: 2019/07/30 15:10:52 by cbrichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** FT_CLEAN/ADD_FLAGS support functions:
**	- FT_OVERRIDE_FLAGS: replaces space/0 by +/- when both are present.
**	- FT_RM_DUP_FLAGS: removes duplicates.
*/

static void	ft_override_flags(t_conv *cv)
{
	int	i;

	i = 0;
	if (ft_c_in_str(' ', cv->flags) && ft_c_in_str('+', cv->flags))
		while (cv->flags[i] != '\0')
		{
			if (cv->flags[i] == ' ')
				cv->flags[i] = '+';
			i++;
		}
	i = 0;
	if (ft_c_in_str('0', cv->flags) && ft_c_in_str('-', cv->flags))
		while (cv->flags[i] != '\0')
		{
			if (cv->flags[i] == '0')
				cv->flags[i] = '-';
			i++;
		}
}

static void	ft_rm_dup_flags(t_conv *cv)
{
	int	i;
	int	j;
	int	skip;

	i = 0;
	j = 0;
	while (cv->flags[i] != '\0')
	{
		j = i + 1;
		skip = 1;
		while (cv->flags[j] != '\0')
		{
			if (cv->flags[j] == cv->flags[i])
			{
				cv->flags[j] = cv->flags[j + skip];
				skip++;
			}
			else
				j++;
		}
		i++;
	}
}

/*
** FT_CLEAN_FLAGS
** OUT: / (updates cv->flags).
** DOES:
**	Calls FT_CLEAN_FLAGS to apply overrides and remove duplicates.
*/

void		ft_clean_flags(t_conv *cv)
{
	ft_override_flags(cv);
	ft_rm_dup_flags(cv);
}

/*
** FT_CLEAN_FLAGS
** OUT: / (updates cv->flags).
** DOES:
**	1) Adds the given new flag to cv->flags.
**	2) Calls FT_CLEAN_FLAGS to apply overrides and remove duplicates.
*/

void		ft_add_flag(char *newf, t_conv *cv)
{
	ft_strcat(cv->flags, newf);
	ft_clean_flags(cv);
}
