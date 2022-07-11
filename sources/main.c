/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:17:29 by Nathanael         #+#    #+#             */
/*   Updated: 2022/07/11 17:17:55 by jbrown           ###   ########.fr       */
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
		get_prompt();
		g_program.pid = 0;
		str = NULL;
		signal(SIGINT, ctrl_handler);
		signal(SIGQUIT, SIG_IGN);
		str = readline(g_program.prompt);
		if (check_blank(str))
			continue ;
		add_history(str);
		split_agrs(str);
		free(str);
		std_sort();
		if (g_program.user_inputs)
			command();
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
	init_global();
	if (!*envp)
	{
		init_noenv(av);
	}
	else
	{
		env_init(envp);
		init_yesenv(av);
	}
	g_program.envp = envp;
	program_loop();
	return (0);
}
