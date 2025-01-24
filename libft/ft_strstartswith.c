/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstartswith.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:34:46 by scraeyme          #+#    #+#             */
/*   Updated: 2025/01/24 15:34:57 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	str_starts_with(const char *str, const char *cmp_str)
{
	int	i;
	int cmp_len;

	i = 0;
	cmp_len = ft_strlen(cmp_str);
	if (!str || !cmp_str)
		return (0);
	while (str[i] && cmp_len > 0)
	{
		if (str[i] != cmp_str[i])
			return (0);
		cmp_len--;
		i++;
	}
	return (1);
}