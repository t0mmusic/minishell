/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 19:41:41 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/05 16:24:29 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

/**
 * @brief	Updates the PWD and OLDPWD environment variables on directory change.
 * @param	path: The path that will be changed to
**/

static void	update_pwd(char *path)
{
	char	*old_pwd;
	char	*new_pwd;
	char	*var;

	chdir(path);
	var = ft_getenv("PWD");
	old_pwd = ft_strjoin("OLDPWD=", var);
	add_env(old_pwd, false);
	ft_tryfree(var);
	ft_tryfree(old_pwd);
	new_pwd = ft_strjoin("PWD=", getcwd(NULL, 0));
	add_env(new_pwd, false);
	ft_tryfree(new_pwd);
	get_prompt();
}

/**
 * @brief	Changes the directory to root if the user does not enter arguments.
**/

static bool	root_directory(void)
{
	update_pwd("/");
	return (true);
}

/**
 * @brief	Takes the location of the current working directory and appends the
 * input path to it.
 * @param	target_dir: the directory we want to go to
 * @returns	path: full path of desired directory
**/

static char	*relative_path(char *target_dir)
{
	char	*path;
	char	*tmp;
	char	buffer[512];

	path = ft_strjoin(getcwd(buffer, sizeof(buffer)), "/");
	tmp = path;
	path = ft_strjoin(path, target_dir);
	ft_tryfree(tmp);
	return (path);
}

/**
 * @brief	Checks the user input path to see if it has no arguments, an agrument
 * for an adjacent directory, or an absolute path. It then checks if that
 * directory is valid or if the user can access it before attempting to redirect.
 * @returns	true: boolean to indicate this is a built-in function
**/

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
	{
		ft_printf_fd("cd: Ain't no %s directory!\n", 1, target_dir);
		g_program.exit_status = 1;
	}
	else
		update_pwd(path);
	ft_tryfree(path);
	return (true);
}
