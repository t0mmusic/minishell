/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nathanael <nervin@student.42adel.org.au    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:24:58 by Nathanael         #+#    #+#             */
/*   Updated: 2022/06/20 17:57:02 by Nathanael        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * todo:	implement file checker for file input, getting current path and
 * returning
**/
void	get_file(char *untrimmed, char *file_result)
{
	while (*untrimmed != '\0')
	{
		if (!ft_isspace(*file_result))
		{
			*file_result = *untrimmed;
			file_result++;
		}
		untrimmed++;
	}
	*file_result = '\0';
	printf("\nBefore: %s\tAfter: %s\n", untrimmed, file_result);
}
