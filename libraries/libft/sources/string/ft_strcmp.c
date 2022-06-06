/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nathanael <nervin@student.42adel.org.au    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 12:29:13 by Nathanael         #+#    #+#             */
/*   Updated: 2022/06/06 14:08:58 by Nathanael        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Compares the contents of two strings and returns how far away the difference is
between them (ASCII comparison).
*/
int	ft_strcmp(char *first_str, char *second_str)
{
	int	index;

	index = 0;
	if (!first_str || !second_str)
		return (EXIT_SUCCESS);
	while (first_str[index] || second_str[index])
	{
		if (first_str[index] == second_str[index])
			index++;
		else
		{
			if (first_str[index] > second_str[index])
				return (1);
			else
				return (-1);
		}
	}
	return (EXIT_SUCCESS);
}
