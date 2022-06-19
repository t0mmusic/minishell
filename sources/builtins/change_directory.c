/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 19:41:41 by jbrown            #+#    #+#             */
/*   Updated: 2022/06/19 15:01:33 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Takes the location of the current working directory and appends the input
	path to it.	*/

static char	*relative_path(char *target_dir)
{
	char	*path;
	char	buffer[512];

	path = getcwd(buffer, sizeof(buffer));
	ft_strlcat(path, "/", ft_strlen(path) + 2);
	ft_strlcat(path, target_dir,  ft_strlen(path) + ft_strlen(target_dir) + 1);
	return (path);
}

/*	Checks the user input path to see if it has no arguments, an agrument for an
	adjacent directory, or an absolute path. It then checks if that directory is
	valid or if the user can access it before attempting to redirect.	*/

bool	change_directory(char *str)
{
	char	*path;
	char	*target_dir;

	target_dir = str + 2;
	while (ft_isspace(*target_dir))
		target_dir++;
	if (!(*target_dir))
		path = "/";
	else if (*target_dir == '/')
		path = target_dir;
	else
		path = relative_path(target_dir);
	if (access(path, F_OK) < 0)
		ft_printf_fd("cd: Ain't no %s directory!\n", 1, target_dir);
	else
		chdir(path);
	return (true);
}
