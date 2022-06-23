/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:17:29 by Nathanael         #+#    #+#             */
/*   Updated: 2022/06/23 16:58:15 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

void	program_loop(int loop)
{
	char	*str;

	str = NULL;
	g_program.pid = 0;
	str = readline(g_program.prompt);
	if (check_blank(str))
		program_loop(1);
	add_history(str);
	split_agrs(str);
	std_sort(getenv("PWD"), g_program.user_inputs);
	if (!inbuilt_check())
	{
		g_program.pid = fork();
		if (!g_program.pid)
		{
			check_pipes();
		}
		waitpid(g_program.pid, 0, 0);
	}
	free(str);
	if (loop)
		program_loop(1);
}

int	main(int ac, char *av[], char *envp[])
{
	(void)ac;
	(void)av;
	init_global();
	g_program.envp = envp;
	signal(SIGINT, ctrl_c_handler);
	program_loop(1);
	return (0);
}
