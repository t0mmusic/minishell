/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_err.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nathanael <nervin@student.42adel.org.au    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 13:03:36 by Nathanael         #+#    #+#             */
/*   Updated: 2022/07/01 13:10:21 by Nathanael        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Log a message to standard error
 * @param	input	The name of the thing to log
 * @param	message	The message to log
 * @param	ret		The return value to return
 * @return	Returns a integer value based on the ret value
**/
int	log_err(char *input, char *message, int ret)
{
	ft_putstr_fd("minishell: ", 2);
	if (input != NULL)
		ft_putstr_fd(input, 2);
	ft_putendl_fd(message, 2);
	return (ret);
}
