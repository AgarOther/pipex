/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:10:41 by scraeyme          #+#    #+#             */
/*   Updated: 2024/10/30 10:37:14 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "./../../libft.h"

int	count_conversions(const char *str);
int	print_conversion(const char *str, va_list arg);
int	ft_putstr(char *s);
int	ft_putchar(int c);
int	ft_putnbr(int n);
int	ft_putlong(size_t n);
int	is_corrupted(const char *str);
int	is_conversion(const char *c);
int	ft_printf_intlen(int n);
int	ft_print_hexadecimal(unsigned int n, int is_upper);
int	ft_print_ptr(unsigned long n);
int	ft_printf(const char *input, ...);
int	ft_longlen(size_t n);
#endif
