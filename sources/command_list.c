/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:46:25 by jbrown            #+#    #+#             */
/*   Updated: 2022/06/20 17:10:09 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Creates a pipeline for the input and output of each command. The input
	is the originally specified input file (by default standard input) and the
	output is the originally specified output file (by default standard output).
	Once all the commands have been excecuted, the final command will be output
	appropriately.	*/

void	pipe_split(t_prog prog)
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
		out_process(prog);
	}
}

/*	Sets the current list of arguments for a command to be executed.
	The list is delimited by a pipe entered by the user, or by the
	end of the input argument list.	*/

void	set_commands(t_prog *prog)
{
	int		i;
	int		j;
	char	**current;

	current = prog->user_inputs;
	i = 0;
	while (current[i] && strcmp("|", current[i]))
	{
		i++;
	}
	if (!current[i])
		prog->commands = current;
	else
	{
		prog->commands = malloc(sizeof(char *) * i);
		j = 0;
		while (j < i)
		{
			prog->commands[j] = current[j];
			j++;
		}
		prog->commands[j] = NULL;
	}
}

/*	Sets the list of commands for the current pipe, then sends it
	to be executed. It then moves to the next list of commands.	*/

void	execute_commands(t_prog *prog)
{
	int	i;

	set_commands(prog);
	pipe_split(*prog);
	i = 0;
	while (*prog->user_inputs && ft_strcmp("|", *prog->user_inputs))
	{
		prog->user_inputs++;
	}
	if (!ft_strcmp("|", *prog->user_inputs))
		prog->user_inputs++;
	free (prog->commands);
	check_pipes(*prog);
}

/*	Checks if there are any pipes in the list of user inputs. If
	there are, it will set the first list of arguments to be
	exeecuted. Otherwise, it will excecute the full list.	*/

void	check_pipes(t_prog prog)
{
	int	i;

	i = 0;
	if (!prog.user_inputs[i])
		exit (0);
	while (prog.user_inputs[i])
	{
		if (!ft_strcmp("|", prog.user_inputs[i]))
			execute_commands(&prog);
		i++;
	}
	prog.commands = prog.user_inputs;
	out_process(prog);
}
