/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:57:22 by jbrown            #+#    #+#             */
/*   Updated: 2022/06/24 15:09:17 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Checks if the user has entered a blank prompt.	*/

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

/*	Gives the user name and current directory for the prompt. This is updated
	each time the user enters a command. Currently causes an issue where an
	extra 9 characters are printed when reviewing history. Still figuring
	out what the cause is.	*/

char	*get_prompt(void)
{
	char	*prompt;
	char	*tmp;
	char	buffer[512];

	prompt = ft_strjoin(getenv("HOME") + 7, "@\x1b[32mminishell\x1b[0m ");
	tmp = prompt;
	prompt = ft_strjoin(tmp, getcwd(buffer, sizeof(buffer)));
	free (tmp);
	tmp = prompt;
	prompt = ft_strjoin(tmp, " $ ");
	free (tmp);
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
