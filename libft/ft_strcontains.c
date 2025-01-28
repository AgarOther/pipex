/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcontains.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 23:10:31 by scraeyme          #+#    #+#             */
/*   Updated: 2025/01/28 23:33:12 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcontains(char *s1, char *s2)
{
	int	i;
	int	s1_len;
	int	s2_len;

	if (!s1 || !s2)
		return (0);
	i = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s2_len > s1_len)
		return (0);
	while (s1[i] && i + s2_len < s1_len)
	{
		if (!ft_strncmp(&s1[i], s2, s2_len))
			return (1);
		i++;
	}
	return (0);
}
