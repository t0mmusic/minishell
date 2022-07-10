/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:46:25 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/10 11:01:18 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

/**
 * @brief	Creates a pipeline for the input and output of each command.
 * The input is the originally specified input file (by default standard input)
 * and the output is the originally specified output file (by default standard
 * output). Once all the commands have been excecuted, the final command will be
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
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		waitpid(pid, 0, 0);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
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
	set_commands();
	pipe_split();
	while (*g_program.user_inputs && ft_strcmp("|", *g_program.user_inputs)
		&& !interp_token(*g_program.user_inputs))
	{
		g_program.user_inputs++;
	}
	if (!ft_strcmp("|", *g_program.user_inputs))
		g_program.user_inputs++;
	free(g_program.commands);
	check_pipes();
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
			execute_commands();
		i++;
	}
	g_program.commands = g_program.user_inputs;
	out_process();
}
