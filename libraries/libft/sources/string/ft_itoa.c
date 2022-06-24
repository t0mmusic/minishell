/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 14:55:33 by jbrown            #+#    #+#             */
/*   Updated: 2022/01/28 09:54:05 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	modsize(long int n)
{
	int	i;

	i = 0;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static int	otherdigits(long int n, int factor)
{
	int	mod;

	mod = 1;
	while (factor)
	{
		mod *= 10;
		factor--;
	}
	return (n % mod);
}

static int	firstdigit(long int n, int i)
{
	while (i)
	{
		n /= 10;
		i--;
	}
	return (n);
}

static char	*fillarr(char *arr, int neg, int digits, long int n)
{
	int	i;

	i = 0;
	if (neg)
	{
		arr[i] = '-';
		n = -n;
		i++;
	}
	while (digits)
	{
		arr[i] = firstdigit(n, digits - 1) + 48;
		n = otherdigits(n, digits - 1);
		digits--;
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

char	*ft_itoa(int n)
{
	int		neg;
	int		digits;
	char	*arr;

	if (n == 0)
	{
		arr = malloc(sizeof(*arr) * 2);
		arr[0] = '0';
		arr[1] = '\0';
		return (arr);
	}
	n = (long int) n;
	digits = modsize(n);
	neg = 0;
	if (n < 0)
		neg = 1;
	arr = malloc(sizeof(*arr) * (neg + digits + 1));
	if (!arr)
		return (NULL);
	arr = fillarr(arr, neg, digits, n);
	return (arr);
}
