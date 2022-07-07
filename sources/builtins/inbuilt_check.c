/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inbuilt_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 19:42:57 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/07 15:01:50 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

/**
 * @brief	Adds a variable that is not a part of the environment variables.
 * When printing the environment variable list, this will not be included, but
 * it can still be called on in the shell
 * @param	var: the variable to be added
 * @returns	boolean true
**/

bool	add_var(char *var)
{
	add_env(var, true);
	return (true);
}

/**
 * @brief	Checks to see if the command entered by the user is one of the
 * recreated inbuilt functions. These functions are executed in the main
 * process to ensure that they are handled in the same way that the real
 * shell handles them.
 * @returns	boolean true if the command was found, false if not.
**/

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
	if (ft_strchr(g_program.user_inputs[0], '='))
		return (add_var(g_program.user_inputs[0]));
	return (false);
}

/**
 * @brief	Checks to see if the command entered by the user is one of the
 * recreated inbuilt functions. These functions are executed in a sub-process
 * to ensure that they are handled in the same way that the real shell handles
 * them.
 * @returns	boolean true if the command was found, false if not.
**/

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
