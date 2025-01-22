/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:24:22 by scraeyme          #+#    #+#             */
/*   Updated: 2024/10/12 19:30:22 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_intlen(int n)
{
	int	len;

	len = 1;
	if (n <= -2147483648)
		return (10);
	n *= (1 + -2 * (n < 0));
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int	ft_longlen(size_t n)
{
	int	len;

	len = 1;
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	return (len);
}
