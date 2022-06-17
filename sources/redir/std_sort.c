/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nathanael <nervin@student.42adel.org.au    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:24:41 by Nathanael         #+#    #+#             */
/*   Updated: 2022/06/17 14:45:19 by Nathanael        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	std_sort(char *path, char **commands)
{
	int	index;

	index = 0;
	while (commands[0][index] != '\0')
	{
		printf("command: %s", commands[0][index]);
		if (commands[0][index] == '>')
			std_output(path);
		else if (commands[0][index] == '>' && commands[0][index + 1] == '>')
			std_output_append(path);
		else if (commands[0][index] == '<')
			std_input(path);
		else if (commands[0][index] == '<' && commands[0][index + 1] == '<')
			std_input_delim(path);
		index++;
	}
	printf("\n");
}
