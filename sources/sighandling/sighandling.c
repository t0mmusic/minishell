/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nathanael <nervin@student.42adel.org.au    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:34:01 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/09 15:55:49 by Nathanael        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

/**
 * @brief	cathes the SIGINT signal sent by ctrl-c. If there is a subprocess
 * running, this will close that process. Otherwise, just re-issues the prompt.
 * @param	sig: integer representing the signal caught
**/

void	ctrl_handler(int sig)
{
	if (sig != SIGINT)
		printf("Invalid Signal Caught!\n");
	g_program.exit_status = 130;
	if (!g_program.pid)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	else
	{
		kill(g_program.pid, SIGKILL);
		printf("\n");
	}
}

/**
 * @brief	Allocates memory for an integer array
 * @return	Returns a static variable that now can be used as the signal status
**/
int	*heredoc_signal_get(void)
{
	static int	*trigger;

	if (!trigger)
	{
		trigger = (int *)malloc(sizeof(int));
		*trigger = 0;
	}
	return (trigger);
}

/**
 * @brief	A handler for when heredoc is activated and you want to exit
 * using ctl c
**/
void	heredoc_handler(int sig)
{
	int	*flag;

	flag = heredoc_signal_get();
	if (sig == SIGINT)
	{
		*flag = 1;
		signal(SIGINT, heredoc_handler);
	}
}
