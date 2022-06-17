/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:24:41 by Nathanael         #+#    #+#             */
/*   Updated: 2022/06/17 15:57:38 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	std_sort(char *path, char **commands)
{
	int	index;

	index = 0;
	while (commands[0][index] != '\0')
	{
//		printf("command: %s", commands[0][index]);
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
