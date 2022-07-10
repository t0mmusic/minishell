/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:58:09 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/10 16:09:11 by jbrown           ###   ########.fr       */
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
	ret = malloc(sizeof(*ret) * (i + 1));
	len = 0;
	while (len < i)
	{
		ret[len] = ft_strdup(arr[len]);
		len++;
	}
	ret[len] = NULL;
	free_array(arr);
	return (ret);
}

char	**realloc_back(char **arr, char *delim)
{
	char	**ret;
	int		i;
	int		len;

	if (!delim || !ft_strcmp(arr[0], delim))
		return (arr);
	i = 0;
	while (arr[i] && ft_strcmp(arr[i], delim))
		i++;
	len = i;
	while (arr[len] && ft_strcmp(arr[len], ""))
		len++;
	ret = malloc(sizeof(*ret) * (len - i + 1));
	len = 0;
	while (arr[i] && ft_strcmp(arr[i], ""))
		ret[len++] = ft_strdup(arr[i++]);
	ret[len] = NULL;
	free_array(arr);
	i = -1;
	if (!ret[1] && !ft_strcmp(ret[0], ")"))
	{
		free_array(ret);
		return (NULL);
	}
	return (ret);
}

void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i] != NULL)
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
