/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:35:35 by scraeyme          #+#    #+#             */
/*   Updated: 2024/10/09 16:45:47 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(int n)
{
	int	len;

	len = 1;
	if (n < 0)
		n *= -1;
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*make_str(char *res, int n, int len)
{
	int	i;
	int	neg;

	i = 0;
	neg = 0;
	if (n < 0)
		neg = 1;
	res[len + neg] = 0;
	if (n < 0)
	{
		n *= -1;
		res[0] = '-';
		i = 1;
		len++;
	}
	while (len > i)
	{
		len--;
		res[len] = n % 10 + '0';
		n /= 10;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		int_len;
	int		neg;

	if (n == -2147483648)
	{
		res = ft_strdup("-2147483648");
		return (res);
	}
	int_len = ft_intlen(n);
	neg = 0;
	if (n < 0)
		neg = 1;
	res = malloc(int_len + neg + 1);
	if (!res)
		return (NULL);
	res = make_str(res, n, int_len);
	return (res);
}
