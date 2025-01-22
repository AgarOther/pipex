/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countwords.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:52:15 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/05 23:49:42 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_countwords(const char *str)
{
	int	i;
	int	strs;
	int	is_spaced;

	i = 0;
	strs = 0;
	is_spaced = 1;
	while (str[i])
	{
		if (is_spaced && !ft_isspace(str[i]))
		{
			is_spaced = 0;
			strs++;
		}
		else if (!is_spaced && ft_isspace(str[i]))
			is_spaced = 1;
		i++;
	}
	return (strs);
}
