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

bool	builtin_echo(t_prog prog)
{
	bool	newline;
	char	**print;

	newline = true;
	if (prog.commands[1] && !ft_strcmp(prog.commands[1], "-n"))
	{
		newline = false;
		prog.commands++;
	}
	prog.commands++;
	print = prog.commands;
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
