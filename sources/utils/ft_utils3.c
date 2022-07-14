/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:38:42 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/14 13:08:20 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

/**
 * @brief	Returns the size of an array of char arrays.
**/

int	ft_array_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

/**
 * @brief	Expands the user input array to include all wildcards found
 * as separate tokens.
 * @param	expand: the new user_inputs array expanded to include wildcards
 * @param	split: the array of wildcard tokens
 * @param	i: the index of the original user_inputs array where split will be
 * inserted
 * @returns	the newly populated array
**/

char	**expand_arr(char **expand, char **split, int i)
{
	int	j;
	int	k;

	k = 0;
	while (k < i)
	{
		expand[k] = ft_strdup(g_program.user_inputs[k]);
		k++;
	}
	j = 1;
	while (split[j])
	{
		expand[k++] = ft_strdup(split[j++]);
	}
	i++;
	while (g_program.user_inputs[i])
	{
		expand[k++] = ft_strdup(g_program.user_inputs[i++]);
	}
	expand[k] = NULL;
	return (expand);
}

/**
 * @brief	Finds the index in user_inputs where the "<WILD>" token is, if it
 * exists. It will then split that token into individual tokens based on spaces
 * and add them into the user_inputs array, maintaining the original order.
**/

void	wild_token(void)
{
	int		i;
	char	**split;
	char	**expand;

	i = 0;
	while (g_program.user_inputs[i]
		&& ft_strncmp(g_program.user_inputs[i], "<WILD>", 6))
		i++;
	if (!g_program.user_inputs[i])
		return ;
	split = ft_split(g_program.user_inputs[i], ' ');
	expand = malloc(sizeof(*expand) * (ft_array_size(g_program.user_inputs)
				+ ft_array_size(split) - 1));
	expand = expand_arr(expand, split, i);
	free_array(g_program.user_inputs);
	free_array(split);
	g_program.user_inputs = expand;
}
