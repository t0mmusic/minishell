/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 19:41:41 by jbrown            #+#    #+#             */
/*   Updated: 2022/06/23 09:46:33 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

/*	Changes the directory to root if the user does not enter any arguments.	*/

static bool	root_directory(void)
{
	chdir("/");
	free(g_program.prompt);
	g_program.prompt = get_prompt();
	return (true);
}

/*	Takes the location of the current working directory and appends the input
	path to it.	*/

static char	*relative_path(char *target_dir)
{
	char	*path;
	char	*tmp;
	char	buffer[512];

	path = ft_strjoin(getcwd(buffer, sizeof(buffer)), "/");
	tmp = path;
	path = ft_strjoin(path, target_dir);
	free (tmp);
	return (path);
}

/*	Checks the user input path to see if it has no arguments, an agrument for an
	adjacent directory, or an absolute path. It then checks if that directory is
	valid or if the user can access it before attempting to redirect.	*/

bool	change_directory(void)
{
	char	*path;
	char	*target_dir;

	target_dir = g_program.user_inputs[1];
	if (!target_dir)
		return (root_directory());
	else if (target_dir[0] == '/')
		path = ft_strdup(target_dir);
	else
		path = relative_path(target_dir);
	if (access(path, F_OK) < 0)
		ft_printf_fd("cd: Ain't no %s directory!\n", 1, target_dir);
	else
	{
		chdir(path);
		free (path);
	}
	free(g_program.prompt);
	g_program.prompt = get_prompt();
	return (true);
}
