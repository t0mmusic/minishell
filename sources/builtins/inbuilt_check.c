/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inbuilt_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 19:42:57 by jbrown            #+#    #+#             */
/*   Updated: 2022/06/20 16:46:41 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	These functions must run in the main process. cd will only affect the
	process it is currently changing, meaning only that process will move to a
	different directory. exit will only exit the process it is used on, which
	must be the main process to properly exit the program. If the user has
	entered an exit value, that will be used for exit.	*/

bool	inbuilt_check(t_prog prog)
{
	if (!ft_strcmp("cd", prog.user_inputs[0]))
		return (change_directory(prog));
	if (!ft_strcmp("exit", prog.user_inputs[0]))
	{
		if (prog.user_inputs[1])
			exit (ft_atoi(prog.user_inputs[1]));
		exit (0);
	}
	return (false);
}

/*	These functions work with pipes and redirects, so they are run in a
	sub process.	*/

bool	inbuilt_subprocess(t_prog prog)
{
	if (!ft_strcmp("echo", prog.commands[0]))
		return (builtin_echo(prog));
	if (!ft_strcmp("pwd", prog.commands[0]))
		return (builtin_pwd());
	// if ("export")
	// 	;
	// if ("unset")
	// 	;
	if (!ft_strcmp("env", prog.commands[0]))
		return (builtin_env(prog));
	return (false);
}
