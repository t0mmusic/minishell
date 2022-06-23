/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nathanael <nervin@student.42adel.org.au    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:17:29 by Nathanael         #+#    #+#             */
/*   Updated: 2022/06/23 13:05:12 by Nathanael        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

/*	Gives the user name and current directory for the prompt. This is updated
	each time the user enters a command.	NOTE: consider making the prompt
	part of the global variable so that it only updates when the current
	directory updates.	*/

char	*get_prompt(void)
{
	char	*prompt;
	char	*tmp;
	char	buffer[512];

	prompt = ft_strjoin("@\x1b[32mminishell\x1b[0m ",
			getcwd(buffer, sizeof(buffer)));
	tmp = prompt;
	prompt = ft_strjoin(tmp, " $ ");
	free (tmp);
	tmp = prompt;
	prompt = ft_strjoin(getenv("HOME") + 7, tmp);
	free(tmp);
	return (prompt);
}

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
		g_program.user_inputs = split_agrs(str);
		std_sort(getenv("PWD"), g_program.user_inputs);
		if (!inbuilt_check())
		{
			pid = fork();
			if (!pid)
			{
				check_pipes();
			}
			waitpid(pid, 0, 0);
		}
		free_inputs(g_program.user_inputs);
		free(str);
	}
	return (0);
}
