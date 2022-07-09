/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:58:09 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/09 17:52:26 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

char	**realloc_front(char **arr, char *delim)
{
	char	**ret;
	int		i;
	int		len;

	i = 0;
	while (arr[i] && ft_strcmp(arr[i], delim))
		i++;
	ret = malloc(sizeof(*ret) * i);
	len = 0;
	while (len < i)
	{
		ret[len] = arr[len];
		len++;
	}
	ret[len] = NULL;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free (arr);
	return (ret);
}

char	**realloc_back(char **arr, char *delim)
{
	char	**ret;
	int		i;
	int		len;

	i = 0;
	while (arr[i] && ft_strcmp(arr[i], delim))
	{
		free(arr[i]);
		i++;
	}
	len = i;
	while (arr[len])
		len++;
	ret = malloc(sizeof(*ret) * len - i);
	len = 0;
	while (arr[i])
		ret[len++] = arr[i++];
	ret[len] = NULL;
	free (arr);
	return (ret);
}

void	free_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

char	**update_array(char **arr)
{
	int		i;
	char	*token;

	i = 0;
	if (!arr)
		return (NULL);
	while (arr[i])
	{
		if (interp_token(arr[i]))
		{
			token = arr[i];
			break ;
		}
		i++;
	}
	if (arr[i])
		return (realloc_back(arr, token));
	free_array(arr);
	return (NULL);
}
