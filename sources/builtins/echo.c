/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:47:38 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/04 14:23:39 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

/**
 * @brief	prints the string input by the user. If the user has added the flag
 * '-n', it will not print a newline.
 * @returns	true: boolean to indicate this is a built-in function
 * ! Needs to print the correct exit status of last process
**/

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
