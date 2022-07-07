/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 15:00:17 by Nathanael         #+#    #+#             */
/*   Updated: 2022/07/07 11:26:07 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	free_tmp(tmp, line)
// {
// 	free(tmp);
// 	free(line);
// }

void	cpy_without(char *s1, char *s2, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (s1[j])
	{
		if (j == i)
			j++;
		s2[k] = s1[j];
		if (s1[j])
			j++;
		k++;
	}
	s2[k] = 0;
}

char	*remove_char(char *str, char c)
{
	int		i;
	int		len;
	char	*ret;

	ret = ft_strdup(str);
	len = ft_strlen(str);
	i = 0;
	while (ret[i])
	{
		if (ret[i] == c)
		{
			free (ret);
			ret = malloc(sizeof(*ret) * len);
			cpy_without(str, ret, i);
			len--;
		}
		i++;
	}
	return (ret);
}
