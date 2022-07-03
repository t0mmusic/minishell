/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:14:15 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/03 14:46:59 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Attempts to free a pointer in a subprocess before freeing normally.
 * ! For testing purposes only.
 * @param	ptr: the pointer to be freed.
 * @returns	exit_status: the exit status of the subprocess.
**/

int	ft_tryfree(void *ptr)
{
	int	pid;
	int	exit_status;

	pid = fork();
	if (!pid)
	{
		free(ptr);
		exit(0);
	}
	waitpid(pid, &exit_status, 0);
	if (!exit_status)
		free(ptr);
	else
		printf("Failed to free: %s at %p\n", (char *)ptr, ptr);
	return (exit_status);
}
