/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nathanael <nervin@student.42adel.org.au    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:24:41 by Nathanael         #+#    #+#             */
/*   Updated: 2022/06/20 11:50:25 by Nathanael        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	std_sort(char *prompt, char *commands)
{
	int		index;

	index = 0;
	ft_putstr_fd(prompt, 0);
	while (commands[index] != '\0')
	{
		if (commands[index] == '>')
		{
			std_output(prompt, &commands[index++]);
		}
		else if (commands[index] == '>' && commands[index + 1] == '>')
			std_output_append(prompt, &commands[index++]);
		else if (commands[index] == '<')
			std_input(prompt, &commands[index++]);
		else if (commands[index] == '<' && commands[index + 1] == '<')
			std_input_delim(prompt, &commands[index++]);
		index++;
	}
	printf("\n");
}
