/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:17:29 by Nathanael         #+#    #+#             */
/*   Updated: 2022/06/23 12:34:04 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

int	main(int ac, char *av[], char *envp[])
{
	char	*str;
	int		pid;

	(void)ac;
	(void)av;
	init_global();
	g_program.envp = envp;
	while (1)
	{
		str = NULL;
		str = readline(g_program.prompt);
		if (!ft_strcmp("", str))
			continue ;
		add_history(str);
		split_agrs(str);
		if (!inbuilt_check())
		{
			pid = fork();
			if (!pid)
			{
				check_pipes();
			}
			waitpid(pid, 0, 0);
		}
		free(str);
	}
	return (0);
}
