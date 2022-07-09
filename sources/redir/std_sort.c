/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:24:41 by Nathanael         #+#    #+#             */
/*   Updated: 2022/07/09 11:53:03 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_redirect(int pid)
{
	free_inputs();
	waitpid(pid, 0, 0);
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

void	std_sort(char **commands)
{
	int		i;
	int		pid;

	if (!check_redirect())
		return ;
	pid = fork();
	if (!pid)
	{
		i = 0;
		while (commands[i])
		{
			if (ft_strcmp(commands[i], ">") == 0)
				std_output(commands[i + 1]);
			else if (ft_strcmp(commands[i], ">>") == 0)
				std_output_append(commands[i + 1]);
			else if (ft_strcmp(commands[i], "<") == 0)
				std_input(commands[i + 1]);
			else if (ft_strcmp(commands[i], "<<") == 0)
				std_input_delim(commands[i + 1]);
			i++;
		}
		command();
		exit(0);
	}
	main_redirect(pid);
}
