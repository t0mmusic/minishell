/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:57:22 by jbrown            #+#    #+#             */
/*   Updated: 2022/06/20 10:56:10 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Splits all of the user inputs into separate strings based mostly on spaces,
	but also based on whether they are in quotes.	*/

char	**split_agrs(char *str)
{
	int		i;
	int		j;
	char	**args;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		if (str[i] == '\'' || str[i] == '\"')
		{
			i++;
			while (str[i] && (str[i] != '\'' || str[i] == '\"'))
		}
			return ;
	}
	return (args);
}

int	ft_isspace(int c)
{
	if (c == '\f' || c =='\n' || c == '\r' || c =='\t' || c == '\v' || c == ' ')
		return (1);
	return (0);
}
