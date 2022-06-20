/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nathanael <nervin@student.42adel.org.au    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:24:41 by Nathanael         #+#    #+#             */
/*   Updated: 2022/06/20 11:02:20 by Nathanael        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	std_sort(char *path, char *commands)
{
	int		index;
	char	**temp;

	index = 0;
	temp = malloc(ft_strlen(commands));
	while (commands[index] != '\0')
	{
		if (commands[index] == '>')
		{
			std_output(path, &commands[index]);
		}
		else if (commands[index] == '>' && commands[index + 1] == '>')
			std_output_append(path);
		else if (commands[index] == '<')
			std_input(path);
		else if (commands[index] == '<' && commands[index + 1] == '<')
			std_input_delim(path);
		index++;
	}
	printf("\n");
}
