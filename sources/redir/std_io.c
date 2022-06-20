/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_io.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nathanael <nervin@student.42adel.org.au    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:45:52 by Nathanael         #+#    #+#             */
/*   Updated: 2022/06/20 11:25:50 by Nathanael        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*get_file(char *commands)
// {
// 	int	i;

// 	i = 0;
// 	while (commands[i] != '\0')
// 	{
// 		printf("%c", commands[i]);
// 		i++;
// 	}
// 	printf("\n");
// 	return (&commands[i]);
// }

/**
 * @brief	Redirects input using the '>' character
 * @param	path	The path to input and then output the file to
**/
void	std_output(char *path, char *commands)
{
	// Use *commands to get the > operator, then use path to output to the dir
	(void)path;
	ft_putstr_fd("Commands: ", 1);
	ft_putstr_fd(commands, 1);
	ft_putstr_fd("\n", 1);
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
