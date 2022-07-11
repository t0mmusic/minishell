/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:40:21 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/11 15:21:59 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

/**
 * @brief	Joins a path to a command, separated by '/'.
 * @param	path: The path of the directory where programs are stored
 * @param	command: The name of the command executable
 * @returns	ret: The combined path and commans, separated by '/'
**/

char	*join_path(char *path, char *command)
{
	char	*tmp;
	char	*ret;

	tmp = ft_strjoin(path, "/");
	ret = ft_strjoin(tmp, command);
	free(tmp);
	return (ret);
}

/**
 * @brief	Checks the command entered by the user against all of the possible
 * paths. If it finds one that matches, it will set the path in the
 * prog structure and return 1. Otherwise, returns 0.
 * @returns	boolean true if command exists, false if not
 * ! Occasionally fails on MacOS, reason unkown.
**/

char	*command_valid(char *path)
{
	char	*tmp;
	int		i;

	if (!access(path, 0))
		return (path);
	i = 0;
	while (g_program.paths[i])
	{
		tmp = join_path(g_program.paths[i], path);
		if (access(tmp, F_OK) >= 0)
		{
			path = tmp;
			return (path);
		}
		free(tmp);
		i++;
	}
	return (NULL);
}

/**
 * @brief	The user enters a command (with arguments). If the command is one
 * of the recreated builtins, the command will be executed internally.
 * Otherwise, the function checks if this is a shell command. If it is,
 * it is executed appropriately. Otherwise, an error message is diplayed
 * ! Issue unresolved, unclear what the issue is
**/

void	out_process(void)
{
	char	*path;

	if (inbuilt_subprocess())
		free_exit(0);
	free_array(g_program.paths);
	path = ft_getenv("PATH");
	g_program.paths = ft_split(path, ':');
	free(path);
	update_envp();
	path = g_program.commands[0];
	path = command_valid(path);
	if (path)
	{
		execve(path, g_program.commands, g_program.envp);
	}
	ft_printf_fd("minishell: %s ain't no command!\n",
		2, g_program.commands[0]);
	free_exit(EXIT_FAILURE);
}
