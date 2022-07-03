/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:57:22 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/03 15:02:32 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Checks if the user has entered a blank prompt
 * @param	str: The users input from the prompt
 * @returns	boolean false if any non-space chars are found, true if not
**/

bool	check_blank(char *str)
{
	int	i;

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
 * @returns	prompt: The prompt for readline, showing user and directory.
**/

char	*get_prompt(void)
{
	char	*prompt;
	char	*tmp;
	char	buffer[512];

	prompt = ft_strjoin(getenv("LOGNAME"), "@\001\x1b[32mminishell\x1b[0m\002 ");
	tmp = prompt;
	prompt = ft_strjoin(tmp, getcwd(buffer, sizeof(buffer)));
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
