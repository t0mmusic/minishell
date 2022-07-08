/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_io.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nathanael <nervin@student.42adel.org.au    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:45:52 by Nathanael         #+#    #+#             */
/*   Updated: 2022/07/08 18:05:31 by Nathanael        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Output Redirection Truncation ">"

 * @param	file	The file name to create if it doesn't exist, or overwrite if
 * it does

 * @return	Returns a check if the file can be accessed, otherwise it will exit
 * back to the main process. 

 * @example
 * echo "test" > output.txt
 * cat output.txt
 *	1	test
**/
int	std_output(char *filename)
{
	int	fd;
	int	pid;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (fd < 0)
	{
		return (check_file_access(filename));
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

/**
 * @brief	Output Redirection Append Mode ">>"

 * @param	file	The file name to create if it doesn't exist, or to add on to
 * if it does exist

 * @return	Returns a check if the file can be accessed, otherwise it will exit
 * back to the main process.

 * @example
 * cat output.txt
 * 	1	test
 * echo "testing123" >> output.txt
 * vim output.txt
 * 	1	test
 * 	2	testing123
*/
int	std_output_append(char *filename)
{
	int		fd;
	int		pid;

	fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
		return (check_file_access(filename));
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

/**
 * @brief	Input Redirection Mode "<"

 * @param	1st Parameter	Parameter Description

 * @return	Return Value

 * @example
 * vim	output.txt
	1	test
	2	testing123	
 *	wc -l < output.txt
	2
**/
int	std_input(char *filename)
{
	int		fd;
	int		pid;

	fd = open(filename, O_RDONLY, 0644);
	if (fd < 0)
		return (check_file_access(filename));
	pid = fork();
	if (!pid)
	{
		dup2(fd, STDIN_FILENO);
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
Input Redirection Using Delimiter
e.g:
$>	vim	output.txt
	1	test
	2	testing123	
$>	wc -l << output.txt
	2
*/
int	std_input_delim(char *filename)
{
	int		fd;
	int		pid;

	fd = open(filename, O_RDONLY, 0644);
	if (fd < 0)
		return (check_file_access(filename));
	pid = fork();
	if (!pid)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
		command();
		exit(0);
	}
	close(fd);
	free_inputs();
	waitpid(pid, 0, 0);
	return (0);
}
