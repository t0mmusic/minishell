/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_codes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 13:28:07 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/12 16:22:22 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

/**
 * @brief	Returns the appropriate exit code for the last executed action
 * @returns	string of error code
 * ! Add more as required
**/

char	*error_code(void)
{
	if (g_program.exit_status == 256)
		return (ft_strdup("127"));
	if (g_program.exit_status == 512)
		return (ft_strdup("2"));
	return (ft_itoa(g_program.exit_status));
}

/**
 * @brief	Modifies the exit status to an appropriate exit code when exiting
 * from a sub-process. This ensures that the main process will recieve the
 * correct exit code.
 * ! Add more as required
**/

void	normalise_exit(void)
{
	if (g_program.exit_status == 256)
		g_program.exit_status = 1;
	if (g_program.exit_status == 512)
		g_program.exit_status = 2;
	g_program.exit_status = g_program.exit_status;
}

void	free_exit(int code)
{
	free_full_env();
	freelist(g_program.env);
	free_array(g_program.user_inputs);
	free(g_program.prompt);
	free_array(g_program.paths);
	check_leaks();
	exit(code);
}
