/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:57:22 by jbrown            #+#    #+#             */
/*   Updated: 2022/06/23 09:47:27 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Gives the user name and current directory for the prompt. This is updated
	each time the user enters a command.	NOTE: consider making the prompt
	part of the global variable so that it only updates when the current
	directory updates.	*/

char	*get_prompt(void)
{
	char	*prompt;
	char	*tmp;
	char	buffer[512];

	prompt = ft_strjoin("@\x1b[32mminishell\x1b[0m ",
			getcwd(buffer, sizeof(buffer)));
	tmp = prompt;
	prompt = ft_strjoin(tmp, " $ ");
	free (tmp);
	tmp = prompt;
	prompt = ft_strjoin(getenv("HOME") + 7, tmp);
	free(tmp);
	return (prompt);
}

/*	Returns the current working directory. Doesn't work at all.	*/

char	*ft_get_cwd(void)
{
	char	buffer[512];

	return (getcwd(buffer, sizeof(buffer)));
}

/*	Determines if the input character is a space.	*/

int	ft_isspace(int c)
{
	if (c == '\f' || c == '\n' || c == '\r'
		|| c == '\t' || c == '\v' || c == ' ')
		return (1);
	return (0);
}
