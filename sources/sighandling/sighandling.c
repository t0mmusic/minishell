/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:34:01 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/04 20:26:00 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

/**
 * @brief	cathes the SIGINT signal sent by ctrl-c. If there is a subprocess
 * running, this will close that process. Otherwise, just re-issues the prompt.
 * @param	sig: integer representing the signal caught
 * ! Requires use of rl_replace_line to function, however cannot get this to
 * ! compile. Looking for solution
**/

void	ctrl_handler(int sig)
{
	if (sig != SIGINT)
		printf("How did you do this???\n");
	g_program.exit_status = 130;
	if (!g_program.pid)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	else
		kill(g_program.pid, SIGKILL);
}
