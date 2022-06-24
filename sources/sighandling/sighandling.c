/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:34:01 by jbrown            #+#    #+#             */
/*   Updated: 2022/06/24 17:16:32 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

/*	If the user enters ctrl-c or ctrl-\, this will catch the signal. ctrl-\ will
	do nothing. If there is a currently running process in the minishell, ctrl-c
	will send the kill signal to it. It will then print the prompt again. WIP.*/

void	ctrl_handler(int sig)
{
	if (sig == SIGQUIT)
		return ;
	ft_printf_fd("\n", 1);
	if (!g_program.pid)
	{
		ft_printf_fd("", 1);
	}
	else
		kill(g_program.pid, SIGKILL);
}
