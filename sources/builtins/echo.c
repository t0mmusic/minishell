/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:47:38 by jbrown            #+#    #+#             */
/*   Updated: 2022/06/20 16:26:04 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	builtin_echo(void)
{
	bool	newline;
	char	**print;

	newline = true;
	if (g_program.commands[1] && !ft_strcmp(g_program.commands[1], "-n"))
	{
		newline = false;
		g_program.commands++;
	}
	g_program.commands++;
	print = g_program.commands;
	while (*print)
	{
		ft_printf_fd("%s", 1, *print);
		print++;
		if (*print)
			ft_printf_fd(" ", 1);
	}
	if (newline)
		ft_printf_fd("\n", 1);
	return (true);
}
