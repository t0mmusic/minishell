/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp_end.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nathanael <nervin@student.42adel.org.au    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:46:03 by Nathanael         #+#    #+#             */
/*   Updated: 2022/06/06 14:08:58 by Nathanael        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Compares two strings s1 to s2 for n characters from the end.
Returns EXIT_SUCCESS (1) if the comparison is equal.
Returns EXIT_FAILURE (0) if the comparison is not equal.
Returns EXIT_ERROR (-1) if the comparison fails.
*/
int	ft_strncmp_end(const char *s1, const char *s2, size_t n)
{
	int				index;
	unsigned char	*str1;
	unsigned char	*str2;

	index = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while ((str1[index] != '\0' && str2[index] != '\0' && \
			str1[index] == str2[index] && index < (int)(n - 1)))
		index++;
	if ((str1[index] == str2[index] || (int)n == 0) && \
			ft_strlen(s1) == ft_strlen(s2))
		return (EXIT_SUCCESS);
	else if ((str1[index] != str2[index] || (int)n != 0) && \
			ft_strlen(s1) != ft_strlen(s2))
		return (EXIT_FAILURE);
	else
		return (EXIT_ERROR);
}
