/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nathanael <nervin@student.42adel.org.au    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:46:25 by jbrown            #+#    #+#             */
/*   Updated: 2022/06/20 10:51:25 by Nathanael        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Creates a pipeline for the input and output of each command. The input
	is the originally specified input file (by default standard input) and the
	output is the originally specified output file (by default standard output).
	Once all the commands have been excecuted, the final command will be output
	appropriately.	*/

void	pipe_split(char *cmd, t_prog prog)
{
	int	pid;
	int	pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid)
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		waitpid(pid, 0, 0);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		out_process(cmd, prog);
	}
}

/*	Excecutes all commands in the pipeline until the last, which
	is executed separately to output to the correct file.	*/

void	execute_commands(char **commands, t_prog prog)
{
	int	i;

	i = 0;
	while (commands[i + 1])
	{
		pipe_split(commands[i], prog);
		i++;
	}
	out_process(commands[i], prog);
}

/*	Seperates each command input by the user by the '|' symbol. Each one of
	these will be executed independently.	*/

void	check_pipes(char *str, t_prog prog)
{
	char	**command_array;

	command_array = ft_split(str, '|');
	execute_commands(command_array, prog);
}
