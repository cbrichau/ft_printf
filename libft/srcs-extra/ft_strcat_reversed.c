/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat_reversed.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrichau <cbrichau@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 14:13:47 by cbrichau          #+#    #+#             */
/*   Updated: 2019/07/21 13:54:09 by cbrichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extra.h"

char	*ft_strcat_reversed(char *s1, char *s2)
{
	int	end_s1;
	int	end_s2;

	end_s1 = ft_strlen(s1) - 1;
	end_s2 = ft_strlen(s2);
	while (end_s1 >= 0)
	{
		s1[end_s1 + end_s2] = s1[end_s1];
		end_s1--;
	}
	end_s2--;
	while (end_s2 >= 0)
	{
		s1[end_s2] = s2[end_s2];
		end_s2--;
	}
	return (s1);
}
