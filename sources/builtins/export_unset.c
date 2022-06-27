/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:01:59 by jbrown            #+#    #+#             */
/*   Updated: 2022/06/27 17:18:56 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

/*	Adds a new environment variable. */

bool	builtin_export(void)
{
	add_env(g_program.user_inputs[1], false);
	return (true);
}

/*	Removes an environment variable if it exists.	*/

bool	builtin_unset(void)
{
	remove_env(g_program.user_inputs[1]);
	return (true);
}
