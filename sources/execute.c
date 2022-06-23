/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:40:21 by jbrown            #+#    #+#             */
/*   Updated: 2022/06/23 10:17:44 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

/*	Joins a path to a command, separated by '/'.	*/

char	*join_path(char *path, char *command)
{
	char	*tmp;
	char	*ret;

	tmp = ft_strjoin(path, "/");
	ret = ft_strjoin(tmp, command);
	free (tmp);
	return (ret);
}

/*	Checks the command entered by the user against all of the possible
	paths. If it finds one that matches, it will set the path in the
	prog structure and return 1. Otherwise, returns 0.	*/

bool	command_valid(void)
{
	char	*tmp;
	int		i;

	if (!access(g_program.path, 0))
		return (true);
	i = 0;
	while (g_program.paths[i])
	{
		tmp = join_path(g_program.paths[i], g_program.path);
		if (!access(tmp, 0))
		{
			g_program.path = tmp;
			return (true);
		}
		free (tmp);
		i++;
	}
	return (false);
}

/*	The user enters a command (with arguments). This is saved into the
	'commands' array in 'prog'. It will then check if the command is
	valid, and will execute it if it is, or print an error if it is not.	*/

void	out_process(void)
{
	if (inbuilt_subprocess())
		exit(0);
	g_program.path = g_program.commands[0];
	if (command_valid())
	{
		execve(g_program.path, g_program.commands, g_program.envp);
	}
	ft_printf_fd("minishell: %s command not found!\n", 1, g_program.path);
	exit (127);
}
