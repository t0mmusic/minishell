/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_io.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:45:52 by Nathanael         #+#    #+#             */
/*   Updated: 2022/06/17 15:57:03 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Redirects input using the '>' character
 * @param	path	The path to input and then output the file to
**/
void	std_output(char *path)
{
	//	Using the path
	//	find the current location and output to the given file
	//	at the given path
	(void)path;
}

/**
 * @brief	Handles the >> redirection using the path and append to an existing
 * file
 * @param	path	The path to redirect to
**/
void	std_output_append(char *path)
{
	(void)path;
}

/**
 * @brief	Handles input redirection to the indicated path
 * <
 * @param	path	The path to input from and read the file at the end
**/
void	std_input(char *path)
{
	(void)path;
}

/**
 * @brief	Handles input redirection using delimiter
 * <<
 * @param	path	The path the input from and read from
**/
void	std_input_delim(char *path)
{
	(void)path;
}
