/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:18:30 by scraeyme          #+#    #+#             */
/*   Updated: 2024/10/09 11:55:03 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*strs1;
	unsigned char	*strs2;

	if (!s1 && !s2)
		return (0);
	i = 0;
	strs1 = (unsigned char *) s1;
	strs2 = (unsigned char *) s2;
	while (i < n)
	{
		if (strs1[i] != strs2[i])
			return (strs1[i] - strs2[i]);
		i++;
	}
	return (0);
}
