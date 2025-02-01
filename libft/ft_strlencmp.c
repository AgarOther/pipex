/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlencmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:36:42 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/01 11:18:33 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlencmp(const char *s1, const char *s2, int ignore_nl)
{
	size_t	i;
	size_t	s1_len;
	size_t	s2_len;

	i = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s1_len - ignore_nl != s2_len)
		return (1);
	while (s1[i] || s2[i])
	{
		if (s1[i] == '\n' && ignore_nl)
			break ;
		else if (s1[i] != s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return (0);
}
