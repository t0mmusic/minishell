/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:12:06 by jbrown            #+#    #+#             */
/*   Updated: 2022/06/16 16:53:07 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Returns the number of digits in a number. Does not
 * account for leading zeroes. */

int	nbrcount(size_t n, int radix)
{
	int	count;

	count = 0;
	while (n)
	{
		n /= radix;
		count++;
	}
	return (count);
}

/* Initialises the format structure, prints characters from the
 * string and keeps a running total of characters printed */

int	ft_printf_fd(char *str, ...)
{
	int		i;
	int		fd;
	int		count;
	va_list	arg;

	va_start(arg, str);
	fd = va_arg(arg, int);
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i++])
		{
			count += basic_print(str[i], arg, fd);
			i++;
		}
		if (str[i] && str[i] != '%')
		{
			ft_putchar_fd(str[i], 1);
			i++;
			count++;
		}
	}
	va_end(arg);
	return (count);
}
