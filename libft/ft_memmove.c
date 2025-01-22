/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:25:02 by scraeyme          #+#    #+#             */
/*   Updated: 2024/10/09 11:55:45 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*strdest;
	unsigned char	*strsrc;

	if (!src && !dest)
		return (dest);
	else if (n == 0)
		return (dest);
	strdest = (unsigned char *) dest;
	strsrc = (unsigned char *) src;
	if (dest > src)
	{
		while (n > 0)
		{
			strdest[n - 1] = strsrc[n - 1];
			n--;
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
