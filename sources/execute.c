/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:40:21 by jbrown            #+#    #+#             */
/*   Updated: 2022/06/17 20:41:35 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	command_valid(t_prog *prog)
{
	char	*tmp;
	int		i;

	if (!access(prog->path, 0))
		return (1);
	i = 0;
	while (prog->paths[i])
	{
		tmp = join_path(prog->paths[i], prog->path);
		if (!access(tmp, 0))
		{
			prog->path = tmp;
			return (1);
		}
		free (tmp);
		i++;
	}
	return (0);
}

/*	The user enters a command (with arguments). This is saved into the
	'commands' array in 'prog'. It will then check if the command is
	valid, and will execute it if it is, or print an error if it is not.	*/

void	out_process(char *str, t_prog prog)
{
	if (inbuilt_subprocess(str))
		exit(0);
	prog.commands = ft_split(str, ' ');
	prog.path = prog.commands[0];
	if (command_valid(&prog))
	{
		execve(prog.path, prog.commands, prog.envp);
	}
	ft_printf_fd("minishell: %s command not found!\n", 1, prog.path);
	exit (1);
}
