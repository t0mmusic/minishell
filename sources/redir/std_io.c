/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_io.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:45:52 by Nathanael         #+#    #+#             */
/*   Updated: 2022/07/08 17:31:40 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Output Redirection
e.g:	echo "test" > output.txt
$> vim output.txt
	1	test
*/
int	std_output(char *path, char *file)
{
	int	fd;
	int	pid;

	(void)path;
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0664);
	if (fd < 0)
	{
		return (check_file_access(file));
	}
	pid = fork();
	if (!pid)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
		command();
		exit(0);
	}
	close(fd);
	free_inputs();
	waitpid(pid, 0, 0);
	return (0);
}

/*
Output Append Mode
e.g:	echo "testing123" >> output.txt (contains test on line 1)
$> vim output.txt
	1	test
	2	testing123
*/
int	std_output_append(char *path, char *file)
{
	int		fd;
	int		pid;

	(void)path;
	fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd < 0)
	{
		return (check_file_access(file));
	}
	pid = fork();
	if (!pid)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
		command();
		exit(0);
	}
	close(fd);
	free_inputs();
	waitpid(pid, 0, 0);
	return (0);
}

/*
Input Redirection
e.g:
$>	vim	output.txt
	1	test
	2	testing123	
$>	wc -l < output.txt
	2
*/
int	std_input(char *path, char *file)
{
	printf("File:%s\n < \nPath: %s\n", path, file);
	return (0);
}

/*
Input Redirection Using Delimiter
e.g:
$>	vim	output.txt
	1	test
	2	testing123	
$>	wc -l << output.txt
	2
*/
int	std_input_delim(char *path, char *file)
{
	int	fd;

	(void)path;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (check_file_access(file));
	// dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}
