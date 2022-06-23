/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_io.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nathanael <nervin@student.42adel.org.au    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:45:52 by Nathanael         #+#    #+#             */
/*   Updated: 2022/06/23 15:58:36 by Nathanael        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Output Redirection
e.g:	echo "test" > output.txt
$> vim output.txt
	1	test
*/
void	std_output(char *path, char *file)
{
	// Output to file using path
	printf("Path:%s\n > \nFile: %s\n", path, file);
}

/*
Output Append Mode
e.g:	echo "testing123" >> output.txt (contains test on line 1)
$> vim output.txt
	1	test
	2	testing123
*/
void	std_output_append(char *path, char *file)
{
	printf("Path:%s\n >> \nFile: %s\n", path, file);
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
void	std_input(char *path, char *file)
{
	printf("File:%s\n < \nPath: %s\n", path, file);
}

/*
Input Redirection Using Delimiter
e.g:
$>	vim	output.txt
	1	test
	2	testing123	
$>	wc -l < output.txt
	2
*/
void	std_input_delim(char *path, char *file)
{
	printf("File:%s\n << \nPath: %s\n", path, file);
}
