/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nathanael <nervin@student.42adel.org.au    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:17:29 by Nathanael         #+#    #+#             */
/*   Updated: 2022/06/20 10:52:14 by Nathanael        ###   ########.fr       */
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

	prompt = ft_strjoin("@\x1b[32mminishell\x1b[0m "
		, getcwd(buffer, sizeof(buffer)));
	tmp = prompt;
	prompt = ft_strjoin(tmp, " $ ");
	free (tmp);
	tmp = prompt;
	prompt = ft_strjoin(getenv("HOME") + 7, tmp);
	free(tmp);
	return (prompt);
}

void	int_handler(int sig)
{
	sig = 3 * 4;
	sig++;
	printf("Lol, no.\n");
	return ;
}

int	main(int ac, char *argv[], char *envp[])
{
	char	*str;
	char	*prompt;
	int		pid;
	t_prog	prog;

	check_args(ac, argv, envp);
	prog.envp = envp;
	prog.paths = ft_split(getenv("PATH"), ':');
	signal(SIGINT, int_handler);
	while (1)
	{
		prompt = get_prompt();
		str = readline(prompt);
		add_history(str);
		if (!inbuilt_check(str))
		{
			std_sort(prog.path, str);
			pid = fork();
			if (!pid)
			{
				check_pipes(str, prog);
			}
			waitpid(pid, 0, 0);
		}
		free(str);
		free(prompt);
	}
	return (0);
}
