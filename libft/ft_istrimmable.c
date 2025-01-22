/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_istrimmable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:16:09 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/14 14:05:46 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_istrimmable(char *str, int c)
{
	int	len;

	if (!str)
		return (0);
	len = ft_strlen(str);
	return (str[0] == c && str[len - 1 - (str[len - 1] == '\n')] == c);
}
