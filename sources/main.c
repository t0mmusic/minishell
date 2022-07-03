/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:17:29 by Nathanael         #+#    #+#             */
/*   Updated: 2022/07/03 15:05:47 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

/**
 * @brief	Loop for the program to continuously call readline
 * ! Needs to accomodate all incoming changes
**/

void	program_loop(void)
{
	char	*str;

	while (1)
	{
		g_program.pid = 0;
		str = NULL;
		str = readline(g_program.prompt);
		if (check_blank(str))
			continue ;
		add_history(str);
		split_agrs(str);
		ft_tryfree(str);
		std_sort(getenv("PWD"), g_program.user_inputs);
		if (!inbuilt_check())
		{
			g_program.pid = fork();
			if (!g_program.pid)
			{
				check_pipes();
			}
			waitpid(g_program.pid, &g_program.exit_status, 0);
		}
	}
}

/**
 * @brief	main function. Initialises global variable and begins program loop
 * @param	ac: number of arguments input (unused)
 * @param	av: array of arguments input (unused)
 * @param	envp: array of environment variables input
 * @returns	0 (should never occour due to program loop)
**/

int	main(int ac, char *av[], char *envp[])
{
	(void)ac;
	(void)av;
	init_global();
	env_init(envp);
	g_program.envp = envp;
	signal(SIGINT, ctrl_handler);
	signal(SIGQUIT, ctrl_handler);
	program_loop();
	return (0);
}
