/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_case.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrichau <cbrichau@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 17:38:56 by cbrichau          #+#    #+#             */
/*   Updated: 2019/07/21 13:53:00 by cbrichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extra.h"

char	*ft_convert_case(char *s)
{
	int	len;
	int	i;

	if (s)
	{
		len = ft_strlen(s);
		i = 0;
		while (i < len)
		{
			if (s[i] >= 'a' && s[i] <= 'z')
				s[i] -= 32;
			else if (s[i] >= 'A' && s[i] <= 'Z')
				s[i] += 32;
			i++;
		}
	}
	return (s);
}
