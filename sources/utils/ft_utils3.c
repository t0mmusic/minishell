/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:38:42 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/11 16:46:08 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

/**
 * ! Need a function to insert wildcards as seperate tokens 
**/

void	remove_space(void)
{
	int	i;

	i = 0;
	while (g_program.user_inputs[i])
	{
		ft_strtrim(g_program.user_inputs[i], " ");
		i++;
	}
}
