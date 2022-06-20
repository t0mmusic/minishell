/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:57:22 by jbrown            #+#    #+#             */
/*   Updated: 2022/06/20 15:07:36 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_cpystr(char *str, int *current)
{
	char	end;
	char	*ret;
	int		i;

	i = *current;
	if (str[i] == '\'' || str[i] == '\"')
	{
		end = str[i];
		i++;
		while (str[i] && str[i] != end)
			i++;
		i++;
	}
	else
	{
		while (str[i] && !ft_isspace(str[i]))
		{
			i++;
		}
	}
	ret = ft_substr(str, *current, i - *current);
	*current = i;
	return (ret);
}

/*	Counts the total number of inputs added by the user. This includes the ones
	that are between quotes.	*/

static int	argcount(char *str)
{
	int		i;
	int		count;
	char	*tmp;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i] && !ft_isspace(str[i]))
		{
			tmp = ft_cpystr(str, &i);
			free (tmp);
			count++;
		}
	}
	return (count);
}

/*	Splits all of the user inputs into separate strings based mostly on spaces,
	but also based on whether they are in quotes.	*/

char	**split_agrs(char *str)
{
	int		i;
	int		count;
	char	**args;

	count = argcount(str);
	args = malloc(sizeof(*args) * (count + 1));
	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i] && !ft_isspace(str[i]))
		{
			args[count] = ft_cpystr(str, &i);
			count++;
		}
	}
	args[count] = NULL;
	return (args);
}

int	ft_isspace(int c)
{
	if (c == '\f' || c == '\n' || c == '\r'
		|| c == '\t' || c == '\v' || c == ' ')
		return (1);
	return (0);
}
