/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inbuilt_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 19:42:57 by jbrown            #+#    #+#             */
/*   Updated: 2022/06/27 16:57:59 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

/*	These functions must run in the main process. cd will only affect the
	process it is currently changing, meaning only that process will move to a
	different directory. exit will only exit the process it is used on, which
	must be the main process to properly exit the program. If the user has
	entered an exit value, that will be used for exit.	*/

bool	inbuilt_check(void)
{
	if (!ft_strcmp("cd", g_program.user_inputs[0]))
		return (change_directory());
	if (!ft_strcmp("export", g_program.user_inputs[0]))
		return (builtin_export());
	if (!ft_strcmp("unset", g_program.user_inputs[0]))
		return (builtin_unset());
	if (!ft_strcmp("exit", g_program.user_inputs[0]))
	{
		if (g_program.user_inputs[1])
			exit (ft_atoi(g_program.user_inputs[1]));
		exit (0);
	}
	return (false);
}

/*	These functions work with pipes and redirects, so they are run in a
	sub process. need to add:*/

bool	inbuilt_subprocess(void)
{
	if (!ft_strcmp("echo", g_program.commands[0]))
		return (builtin_echo());
	if (!ft_strcmp("pwd", g_program.commands[0]))
		return (builtin_pwd());
	if (!ft_strcmp("env", g_program.commands[0]))
		return (builtin_env());
	return (false);
}
