/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:57:22 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/05 16:24:51 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "colours.h"

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
 * @brief	Joins to malloced strings and frees them before returning
 * @param	s1: first malloced string
 * @param	s2: second malloced string
 * @returns	joined strings
**/

char	*ft_free_join(char *s1, char *s2)
{
	char	*tmp;

	tmp = s1;
	s1 = ft_strjoin(tmp, s2);
	free(tmp);
	free(s2);
	return (s1);
}

/**
 * @brief	Gives colour to a string of text
 * @param	str: input string to be coloured
 * @param	colour: ansii value of desired colour
 * @returns	str: with updated colour
**/

char	*ft_ansii(char *str, char *colour)
{
	str = ft_strjoin(colour, str);
	str = ft_free_join(str, ft_strdup(DEFAULT));
	return (str);
}

/**
 * @brief	Gives the user name and current directory for the prompt.
 * This is updated each time the user enters a command.
 * ! Currently causing issue on MacOS due to colour
 * ! Unfortunately, solution may be to omit colour...
 * @returns	prompt: The prompt for readline, showing user and directory.
 * ! Add option to change prompt to environment variable PS1
**/

void	get_prompt(void)
{
	char	*prompt;
	char	*user_prompt;

	free(g_program.prompt);
	user_prompt = ft_getenv("PS1");
	if (!check_blank(user_prompt))
	{
		g_program.prompt = user_prompt;
		return ;
	}
	free(user_prompt);
	prompt = ft_free_join(ft_getenv("LOGNAME"), ft_strdup("@"));
	prompt = ft_free_join(prompt, ft_ansii("minishell ", GREEN));
	prompt = ft_free_join(prompt, ft_ansii(ft_getenv("PWD"), GREY));
	prompt = ft_free_join(prompt, ft_ansii(" $ ", BLUE));
	g_program.prompt = prompt;
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
