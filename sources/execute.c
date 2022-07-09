/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nathanael <nervin@student.42adel.org.au    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:40:21 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/09 22:35:33 by Nathanael        ###   ########.fr       */
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
	ft_tryfree(tmp);
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
		ft_tryfree(tmp);
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

	free(g_program.paths);
	g_program.paths = ft_split(ft_getenv("PATH"), ':');
	update_envp();
	if (inbuilt_subprocess())
		exit(0);
	path = g_program.commands[0];
	path = command_valid(path);
	if (path)
	{
		execve(path, g_program.commands, g_program.envp);
		exit(1);
	}
	ft_printf_fd("minishell: %s ain't no command!\n",
		2, g_program.commands[0]);
	exit (EXIT_FAILURE);
}
