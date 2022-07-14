/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:46:25 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/14 09:51:22 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

/**
 * @brief	Creates a pipeline for the input and output of each command.
 * The input is the originally specified input file (by default standard input)
 * and the output is the originally specified output file (by default standard
 * output). Once all the commands have been executed, the final command will be
 * output appropriately.
**/

void	pipe_split(void)
{
	int	pid;
	int	pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid)
	{
		if (!g_program.pid)
			g_program.pid = pid;
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		out_process();
	}
}

/**
 * @brief	Sets the current list of arguments for a command to be executed.
 * The list is delimited by a pipe entered by the user, or by the end of the
 * input argument list.
 * ! Add error for unexpected pipe or whatever at end of arg list
**/

void	set_commands(void)
{
	int		i;
	int		j;
	char	**current;

	current = g_program.user_inputs;
	i = 0;
	while (current[i] && strcmp("|", current[i]))
		i++;
	if (!current[i])
	{
		g_program.commands = current;
	}
	else
	{
		g_program.commands = malloc(sizeof(*g_program.commands) * (i + 1));
		j = 0;
		while (j < i)
		{
			g_program.commands[j] = current[j];
			j++;
		}
		g_program.commands[i] = NULL;
	}
}

/**
 * @brief	Sets the list of commands for the current pipe, then sends it
 * to be executed. It then moves to the next list of commands.
**/

void	execute_commands(void)
{
	int	i;

	set_commands();
	pipe_split();
	i = 0;
	while (g_program.user_inputs[i] && ft_strcmp("|", g_program.user_inputs[i])
		&& !interp_token(g_program.user_inputs[i]))
	{
		i++;
	}
	if (!ft_strcmp("|", g_program.user_inputs[i]))
	{
		g_program.user_inputs = realloc_back(g_program.user_inputs, "|");
		g_program.user_inputs = realloc_back(g_program.user_inputs,
				g_program.user_inputs[1]);
	}
	i = 0;
	free(g_program.commands);
}

/**
 * @brief	If no pipes have been used, g_program.pid will equal zero and the
 * 			command will execute normally. Otherwise, the command will be
 * 			executed in a sub-process, and the main process will wait for the
 * 			first and last commands to execute before returning to the prompt.
**/

void	last_command(void)
{
	int	pid;

	if (!g_program.pid)
		out_process();
	pid = fork();
	if (!pid)
		out_process();
	waitpid(g_program.pid, &g_program.exit_status, 0);
	waitpid(pid, &g_program.exit_status, 0);
	normalise_exit();
	free_exit(g_program.exit_status);
}

/**
 * @brief	Checks if there are any pipes in the list of user inputs. If there
 * are, it will set the first list of arguments to be executed. Otherwise,
 * it will excecute the full list.
**/

void	check_pipes(void)
{
	int	i;

	i = 0;
	if (!g_program.user_inputs[i])
		exit (0);
	while (g_program.user_inputs[i])
	{
		if (interp_token(g_program.user_inputs[i])
			|| !ft_strcmp(">", g_program.user_inputs[i])
			|| !ft_strcmp(">>", g_program.user_inputs[i]))
		{
			g_program.user_inputs[i] = NULL;
			break ;
		}
		if (!ft_strcmp("|", g_program.user_inputs[i]))
		{
			execute_commands();
			i = -1;
		}
		i++;
	}
	g_program.commands = g_program.user_inputs;
	last_command();
}
