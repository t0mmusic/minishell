/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:57:22 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/04 10:48:14 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Checks if the user has entered a blank prompt
 * If the user has entered ctrl-d, str will be NULL, and the program will exit
 * @param	str: The users input from the prompt
 * @returns	boolean false if any non-space chars are found, true if not
**/

bool	check_blank(char *str)
{
	int	i;

	if (!str)
		exit (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief	Gives the user name and current directory for the prompt.
 * This is updated each time the user enters a command.
 * ! Currently causing issue on MacOS due to colour
 * ! Unfortunately, solution may be to omit colour...
 * @returns	prompt: The prompt for readline, showing user and directory.
**/

char	*get_prompt(void)
{
	char	*prompt;
	char	*tmp;
	char	*pwd;

	prompt = ft_strjoin(getenv("LOGNAME"), "@minishell ");
	tmp = prompt;
	pwd = ft_getenv("PWD");
	prompt = ft_strjoin(tmp, pwd);
	free(pwd);
	ft_tryfree(tmp);
	tmp = prompt;
	prompt = ft_strjoin(tmp, " $ ");
	ft_tryfree(tmp);
	return (prompt);
}

/**
 * @brief	Determines if the input character is a space
 * @param	c: character that is being checked
 * @returns	1 if space, 0 if not
**/

int	ft_isspace(int c)
{
	if (c == '\f' || c == '\n' || c == '\r'
		|| c == '\t' || c == '\v' || c == ' ')
		return (1);
	return (0);
}
