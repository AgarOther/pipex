/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:09:21 by scraeyme          #+#    #+#             */
/*   Updated: 2024/10/12 18:57:45 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int n)
{
	int	val;

	val = ft_printf_intlen(n);
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	else if (n >= 0 && n <= 9)
		ft_putchar(n + '0');
	else if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putchar(n % 10 + '0');
	}
	else if (n < 0)
	{
		ft_putchar('-');
		val++;
		n *= -1;
		ft_putnbr(n);
	}
	return (val);
}

int	ft_putlong(size_t n)
{
	int	val;

	val = ft_longlen(n);
	if (n == 0)
		ft_putchar('0');
	else if (n > 0 && n <= 9)
		ft_putchar(n + '0');
	else if (n > 9)
	{
		ft_putlong(n / 10);
		ft_putchar(n % 10 + '0');
	}
	return (val);
}
