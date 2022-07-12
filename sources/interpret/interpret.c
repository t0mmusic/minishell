/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 19:25:43 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/06 19:53:22 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

/**
 * @brief	checks the user inputs for a few different opertators:
 * * ;  : everything following this will be executed seperately from what has
 * *	  been executed already
 * * && : If the previous execution had an exit status of 0, execute the next
 * *	  set of commands
 * * || : If the previous execution did NOT have an exit status of 0, execute the
 * *	  next set of commands
 * ! WIP
**/

void	check_bonus(void)
{
	int		i;
	char	**inputs;

	i = 0;
	inputs = g_program.user_inputs;
	while (inputs[i])
	{
		if (!ft_strcmp(inputs[i], ";"))
			return ; //execute seperately to last command
		if (!ft_strcmp(inputs[i], "&&"))
			return ; //execute if exit_status == 0
		if (!ft_strcmp(inputs[i], "||"))
			return ; //execute if exit_status != 0
		i++;
	}
}
