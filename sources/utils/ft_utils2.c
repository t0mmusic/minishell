/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 15:00:17 by Nathanael         #+#    #+#             */
/*   Updated: 2022/07/08 15:53:32 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	free_tmp(tmp, line)
// {
// 	free(tmp);
// 	free(line);
// }

/**
 * @brief	Incremements through user_inputs, freeing each pointer
**/

void	iterate_user_inputs(void)
{
	char	*tmp;

	tmp = *g_program.user_inputs;
	g_program.user_inputs++;
	free(tmp);
}

/**
 * @brief	Applies a function to every node of a list
 * @param	lst: the list
 * @param	lst: the function to be applied
**/

void	ft_lstall(t_list *lst, char *(*f)(char *))
{
	while (lst != NULL)
	{
		lst->content = f(lst->content);
		lst = lst->next;
	}
}

/**
 * @brief	Copies a string while cutting out a section
 * @param	s1: the original string
 * @param	s2: the destination string
 * @param	i: the starting index to disclude from s2
 * @param	len: the length to disclude from s2
**/

void	cpy_without(char *src, char *dst, int i, int len)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (src[j])
	{
		if (j == i)
		{
			while (len)
			{
				len--;
				j++;
			}
		}
		dst[k] = src[j];
		if (src[j])
			j++;
		k++;
	}
	dst[k] = 0;
}

/**
 * @brief	Removes a substring from the main string
 * @param	s1: the main string
 * @param	s2: the string to be removed from the main
 * @returns	the shortened main string
**/

char	*remove_str(char *s1, char *s2)
{
	int		i;
	int		len;
	int		len2;
	char	*ret;

	len = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len <= len2)
		return (s1);
	ret = ft_strdup(s1);
	i = 0;
	while (ret[i])
	{
		if (!ft_strncmp(&s1[i], s2, len2))
		{
			free (ret);
			ret = malloc(sizeof(*ret) * len - len2 + 1);
			cpy_without(s1, ret, i, len2);
			free (s1);
			s1 = ft_strdup(ret);
			len = ft_strlen(s1);
		}
		i++;
	}
	return (ret);
}
