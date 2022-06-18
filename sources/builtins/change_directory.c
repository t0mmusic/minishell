/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 19:41:41 by jbrown            #+#    #+#             */
/*   Updated: 2022/06/17 20:38:50 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Currently, this works with adjacent directories. Needs to be modified to
	change to any directory given.	*/

bool	change_directory(char *str)
{
	char	*path;
	char	*target_dir;
	char	buffer[512];

	target_dir = str + 2;
	while (*target_dir == ' ')
		target_dir++;
	path = getcwd(buffer, sizeof(buffer));
	ft_strlcat(path, "/", ft_strlen(path) + 2);
	ft_strlcat(path, target_dir,  ft_strlen(path) + ft_strlen(target_dir) + 1);
	if (access(path, F_OK) < 0)
		ft_printf_fd("cd: Ain't no %s directory!\n", 1, target_dir);
	else
	{
		chdir(path);
	}
	return (true);
}
