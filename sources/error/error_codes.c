/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_codes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 13:28:07 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/06 13:45:03 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

/**
 * @brief	Returns the appropriate exit code for the last executed action
 * @returns	string of error code
 * ! Add more as required
**/

char	*error_code(void)
{
	if (g_program.exit_status == 256)
		return (ft_strdup("127"));
	if (g_program.exit_status == 512)
		return (ft_strdup("2"));
	return (ft_itoa(g_program.exit_status));
}
