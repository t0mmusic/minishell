/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 19:06:45 by jbrown            #+#    #+#             */
/*   Updated: 2022/06/19 17:06:23 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	builtin_pwd(void)
{
	ft_printf_fd("%s\n", 1, getenv("PWD"));
	return (true);
}

/*	Prints the environment variables of the system.	Doesn't like pwd for some
	reason.	*/

bool	builtin_env(t_prog prog)
{
	while (*prog.envp)
	{
		printf("%s\n", *prog.envp);
		prog.envp++;
	}
	return (true);
}
