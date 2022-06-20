/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:47:38 by jbrown            #+#    #+#             */
/*   Updated: 2022/06/20 10:14:46 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_next_word(char *str)
{
	while (*str && !ft_isspace(*str))
		str++;
	while (*str && ft_isspace(*str))
		str++;
	return (str);
}

bool	builtin_echo(char *str)
{
	bool	newline;

	newline = true;
	if (ft_strnstr(str, "-n", 7))
	{
		newline = false;
	}
	str = find_next_word(str);
	if (!newline)
		str = find_next_word(str);
	ft_printf_fd("%s", 1, str);
	if (newline)
		ft_printf_fd("\n", 1);
	return (true);
}
