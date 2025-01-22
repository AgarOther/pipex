/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:37:12 by scraeyme          #+#    #+#             */
/*   Updated: 2024/10/14 09:14:02 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*subcat(char *str, char const *s, unsigned int start, size_t k)
{
	int	i;

	i = 0;
	k += start;
	while (s[start] && start < k)
	{
		str[i] = (char) s[start];
		i++;
		start++;
	}
	str[i] = 0;
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	k;

	k = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		str = malloc(1);
		if (!str)
			return (NULL);
		str[0] = 0;
		return (str);
	}
	while (s[start] && k < len)
	{
		start++;
		k++;
	}
	str = malloc(k + 1);
	if (!str)
		return (NULL);
	str = subcat(str, s, start - k, k);
	return (str);
}
