/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:34:01 by jbrown            #+#    #+#             */
/*   Updated: 2022/06/23 16:32:10 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

/*	If the user enters ctrl-c, this will catch the signal. If there is a
	currently running process in the minishell, it will send the kill signal to 
	it. It will then print the prompt again. WIP.	*/

void	ctrl_c_handler(int sig)
{
	(void)sig;
	if (g_program.pid)
		kill(g_program.pid, SIGKILL);
	ft_printf_fd("\n%s", 1, get_prompt());
}
