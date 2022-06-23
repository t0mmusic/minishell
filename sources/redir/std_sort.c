/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nathanael <nervin@student.42adel.org.au    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:24:41 by Nathanael         #+#    #+#             */
/*   Updated: 2022/06/23 13:06:17 by Nathanael        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	std_sort(char *path, char **commands)
{
	int		i;

	i = 0;
	while (commands[i])
	{
		if (ft_strcmp(commands[i], ">") == 0)
		{
			std_output(path, *commands[i]);
		}
		else if (ft_strcmp(commands[i], ">>") == 0)
		{
			std_output_append(path, *commands);
		}
		else if (ft_strcmp(commands[i], "<") == 0)
		{
			std_input(path, *commands[i]);
		}
		else if (ft_strcmp(commands[i], "<<") == 0)
		{
			std_input_delim(path, *commands);
		}
		i++;
	}
}
