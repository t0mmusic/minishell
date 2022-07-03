/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:24:41 by Nathanael         #+#    #+#             */
/*   Updated: 2022/07/03 14:38:11 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_file_access(char *file)
{
	struct stat	buf;

	if (stat(file, &buf) == 0)
	{
		if (buf.st_mode & S_IFDIR)
		{
			printf("Comparison: %d", buf.st_mode & S_IFDIR);
			return (log_err(file, ": is a directory", 1));
		}
		else if ((buf.st_mode & S_IXUSR) == 0)
		{
			printf("Comparison: %d", buf.st_mode & S_IXUSR);
			return (log_err(file, ": permission denied", 1));
		}
	}
	return (log_err(file, ": no such file or directory", 1));
}

void	std_sort(char *path, char **commands)
{
	int		i;

	i = 0;
	while (commands[i])
	{
		if (ft_strcmp(commands[i], ">") == 0)
			std_output(path, commands[i + 1]);
		else if (ft_strcmp(commands[i], ">>") == 0)
			std_output_append(path, commands[i + 1]);
		else if (ft_strcmp(commands[i], "<") == 0)
			std_input(path, commands[i + 1]);
		else if (ft_strcmp(commands[i], "<<") == 0)
			std_input_delim(path, commands[i + 1]);
		i++;
	}
}
