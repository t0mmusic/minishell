/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inbuilt_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 19:42:57 by jbrown            #+#    #+#             */
/*   Updated: 2022/06/17 19:50:37 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	These functions must run in the main process. cd will only affect the
	process it is currently changing, meaning only that process will move to a
	different directory. exit will only exit the process it is used on, which
	must be the main process to properly exit the program.	*/

bool	inbuilt_check(char *str)
{
	if (!ft_strncmp("cd", str, 2))
		return (change_directory(str));
	if (!ft_strcmp("exit", str))
		exit (0);
	return (false);
}

bool	inbuilt_subprocess(char *str)
{
	// if ("echo")
	// 	;
	if (!ft_strcmp("pwd", str))
		return(builtin_pwd());
	// if ("export")
	// 	;
	// if ("unset")
	// 	;
	if (!ft_strcmp("env", str))
		return(builtin_env());
	return (false);
}
