/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 08:54:50 by jbrown            #+#    #+#             */
/*   Updated: 2022/06/16 16:42:07 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Prints a number in the chosen radix. Distinguishes
 * between upper and lower case hexidecimal. */

static int	putnbr_radix(size_t n, size_t radix, char up, int fd)
{
	if (!n)
	{
		ft_putchar_fd('0', fd);
		return (1);
	}
	if (n >= radix)
	{
		putnbr_radix(n / radix, radix, up, fd);
		putnbr_radix(n % radix, radix, up, fd);
	}
	if (n < radix)
	{
		if (n > 9)
		{
			if (up == 'X')
				ft_putchar_fd(n + 55, fd);
			else
				ft_putchar_fd(n + 87, fd);
		}
		else
			ft_putchar_fd(n + '0', fd);
	}
	return (nbrcount(n, radix));
}

/* Used as a precheck for integers. If input is negative,
 * it will be flipped to positive and '-' will be printed */

static int	negcheck(long long int n, int fd)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
		count++;
	}
	return (putnbr_radix(n, 10, 0, fd) + count);
}

/* Same functionality as putchar, but returns length */

static int	basic_char(char c, int fd)
{
	ft_putchar_fd(c, fd);
	return (1);
}

/* prints a string or "(null)" if the string is empty,
 * then returns the string length. */

static int	basic_str(char *str, int fd)
{
	if (!str)
	{
		ft_putstr_fd("(null)", fd);
		return (6);
	}
	ft_putstr_fd(str, fd);
	return (ft_strlen(str));
}

/* This function is used when no flags are applied to
 * the output. It does not require memory allocation. */

int	basic_print(char c, va_list v, int fd)
{
	if (c == 'i' || c == 'd')
		return (negcheck(va_arg(v, int), fd));
	if (c == 'u')
		return (putnbr_radix(va_arg(v, unsigned int), 10, c, fd));
	if (c == 'x' || c == 'X')
		return (putnbr_radix(va_arg(v, unsigned int), 16, c, fd));
	if (c == 'p')
	{
		ft_putstr_fd("0x", fd);
		return (putnbr_radix(va_arg(v, unsigned long), 16, c, fd));
	}
	if (c == 'c')
		return (basic_char(va_arg(v, int), fd));
	if (c == 's')
		return (basic_str(va_arg(v, char *), fd));
	if (c == '%')
		return (basic_char('%', fd));
	return (0);
}
