/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_io.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nathanael <nervin@student.42adel.org.au    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:45:52 by Nathanael         #+#    #+#             */
/*   Updated: 2022/07/11 14:04:56 by Nathanael        ###   ########.fr       */
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
	g_program.user_inputs = realloc_back(g_program.user_inputs,
			g_program.user_inputs[2]);
	return (-1);
}

/**
 * @brief	Input Redirection Mode "<<"

 * @param	delim	The character to stop the heredoc from executing

 * @return	Returns -1

 * @example
 * ls << b
	heredoc> a
	heredoc> b
 * <ls output of current directory>
**/
int	std_input_delim(char *delim)
{
	int		fd;
	int		*sigstatus;

	fd = open(HERE_DOC_TMPFILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (check_file_access(HERE_DOC_TMPFILE));
	here_doc(fd, delim);
	sigstatus = heredoc_signal_get();
	free(sigstatus);
	close(fd);
	g_program.user_inputs = realloc_back(g_program.user_inputs,
			g_program.user_inputs[2]);
	return (-1);
}
