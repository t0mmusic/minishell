/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_io.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:45:52 by Nathanael         #+#    #+#             */
/*   Updated: 2022/07/09 15:12:23 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

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

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (fd < 0)
	{
		return (check_file_access(filename));
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	command();
	normalise_exit();
	exit(g_program.exit_status);
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

	fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
		return (check_file_access(filename));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	command();
	normalise_exit();
	exit(g_program.exit_status);
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

	fd = open(filename, O_RDONLY, 0644);
	if (fd < 0)
		return (check_file_access(filename));
	dup2(fd, STDIN_FILENO);
	close(fd);
	iterate_user_inputs();
	iterate_user_inputs();
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
int	std_input_delim(char *delim)
{
	int		fd;

	fd = open(HERE_DOC_TMPFILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (check_file_access(HERE_DOC_TMPFILE));
	here_doc(&fd, delim);
	close(fd);
	iterate_user_inputs();
	iterate_user_inputs();
	return (0);
}
