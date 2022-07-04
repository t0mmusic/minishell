/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:34:01 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/04 11:03:57 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

/**
 * @brief	cathes the SIGINT signal sent by ctrl-c. If there is a subprocess
 * running, this will close that process. Otherwise, just re-issues the prompt.
 * @param	sig: integer representing the signal caught
 * ! Does not perfectly handle reprompting the user. Should be resetting the
 * ! prompt before giving it back to user. Possibly not an issue.
**/

void	ctrl_handler(int sig)
{
	if (sig != SIGINT)
		printf("How did you do this???");
	ft_printf_fd("\n", 1);
	if (!g_program.pid)
	{
		ft_printf_fd(g_program.prompt, 1);
	}
	else
		kill(g_program.pid, SIGKILL);
}
