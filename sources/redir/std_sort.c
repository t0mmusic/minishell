/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:24:41 by Nathanael         #+#    #+#             */
/*   Updated: 2022/07/11 11:49:55 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_redirect(void)
{
	free_inputs();
	waitpid(g_program.pid, &g_program.exit_status, 0);
}

bool	check_redirect(void)
{
	int	i;

	i = 0;
	while (g_program.user_inputs[i])
	{
		if (!ft_strcmp(g_program.user_inputs[i], ">")
			|| !ft_strcmp(g_program.user_inputs[i], ">>")
			|| !ft_strcmp(g_program.user_inputs[i], "<")
			|| !ft_strcmp(g_program.user_inputs[i], "<<"))
			return (true);
		i++;
	}
	return (false);
}

int	check_file_access(char *file)
{
	struct stat	buf;

	if (stat(file, &buf) == 0)
	{
		if (buf.st_mode & S_IFDIR)
		{
			return (log_err(file, ": is a directory", 1));
		}
		else if ((buf.st_mode & S_IXUSR) == 0)
		{
			return (log_err(file, ": permission denied", 1));
		}
	}
	return (log_err(file, ": no such file or directory", 1));
}

/**
 * ! need to make sure that commands is equal to the user_inputs to
 * ! prevent heap use after free
**/

void	std_sort(char **commands)
{
	int		i;

	(void)commands;
	if (!check_redirect())
		return ;
	g_program.pid = fork();
	if (!g_program.pid)
	{
		i = 0;
		while (g_program.user_inputs[i])
		{
			if (ft_strcmp(g_program.user_inputs[i], ">") == 0)
				std_output(g_program.user_inputs[i + 1]);
			else if (ft_strcmp(g_program.user_inputs[i], ">>") == 0)
				std_output_append(g_program.user_inputs[i + 1]);
			else if (ft_strcmp(g_program.user_inputs[i], "<") == 0)
				i = std_input(g_program.user_inputs[i + 1]);
			else if (ft_strcmp(g_program.user_inputs[i], "<<") == 0)
				i = std_input_delim(g_program.user_inputs[i + 1]);
			i++;
		}
		command();
		normalise_exit();
		exit(g_program.exit_status);
	}
	main_redirect();
}
