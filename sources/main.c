/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:17:29 by Nathanael         #+#    #+#             */
/*   Updated: 2022/06/20 17:07:00 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	*prompt;
	int		pid;
	t_prog	prog;

	(void)ac;
	(void)av;
	prog.envp = envp;
	prog.paths = ft_split(getenv("PATH"), ':');
	while (1)
	{
		prompt = get_prompt();
		str = readline(prompt);
		add_history(str);
		prog.user_inputs = split_agrs(str);
//		std_sort(prompt, str);
		if (!inbuilt_check(prog))
		{
			pid = fork();
			if (!pid)
			{
				check_pipes(prog);
			}
			waitpid(pid, 0, 0);
		}
		free_inputs(prog.user_inputs);
		free(str);
		free(prompt);
	}
	return (0);
}
