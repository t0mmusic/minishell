/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:01:59 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/04 11:22:42 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

/**
 * @brief	Adds a new environment variable.
 * @returns	true: boolean to indicate this is a built-in function
**/

bool	builtin_export(void)
{
	add_env(g_program.user_inputs[1], false);
	return (true);
}

/**
 * @brief	Removes an environment variable if it exists.
 * @returns	true: boolean to indicate this is a built-in function
**/

bool	builtin_unset(void)
{
	remove_env(g_program.user_inputs[1]);
	return (true);
}
