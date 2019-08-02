/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrichau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:58:06 by cbrichau          #+#    #+#             */
/*   Updated: 2019/04/25 15:52:07 by cbrichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*s1_pt;
	unsigned char	*s2_pt;

	s1_pt = (unsigned char *)s1;
	s2_pt = (unsigned char *)s2;
	while (*s1_pt && *s2_pt && *s1_pt == *s2_pt)
	{
		s1_pt++;
		s2_pt++;
	}
	return ((int)*s1_pt - *s2_pt);
}
