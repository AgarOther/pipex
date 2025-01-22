/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa_conversion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 22:19:16 by scraeyme          #+#    #+#             */
/*   Updated: 2024/10/30 10:36:44 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_revstr(char *str)
{
	int		i;
	int		len;
	char	temp;

	i = 0;
	len = ft_strlen(str);
	while (i < len / 2)
	{
		temp = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = temp;
		i++;
	}
	return (str);
}

static char	*get_hex_str(char *hex, unsigned int n, char *str)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		str[i] = (hex[n % 16]);
		n /= 16;
		i++;
	}
	str[i] = 0;
	str = ft_revstr(str);
	return (str);
}

int	ft_print_hexadecimal(unsigned int n, int is_upper)
{
	char	*hex;
	char	*str;
	int		val;

	hex = "0123456789ABCDEF";
	if (n == 0)
	{
		ft_putchar('0');
		return (1);
	}
	val = ft_longlen(n);
	str = malloc(val + 1);
	if (!str)
		return (-1);
	if (!is_upper)
		hex = "0123456789abcdef";
	str = get_hex_str(hex, n, str);
	ft_putstr(str);
	val = ft_strlen(str);
	free(str);
	return (val);
}

static char	*get_ptr_str(char *hex, unsigned long n, char *str)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		str[i] = (hex[n % 16]);
		n /= 16;
		i++;
	}
	str[i] = 0;
	str = ft_revstr(str);
	return (str);
}

int	ft_print_ptr(unsigned long n)
{
	char	*hex;
	char	*str;
	int		val;

	if (n == 0)
	{
		ft_putstr("(nil)");
		return (5);
	}
	hex = "0123456789abcdef";
	ft_putstr("0x");
	val = ft_longlen(n) + 2;
	str = malloc(val + 1);
	if (!str)
		return (-1);
	str = get_ptr_str(hex, n, str);
	ft_putstr(str);
	val = ft_strlen(str) + 2;
	free(str);
	return (val);
}
