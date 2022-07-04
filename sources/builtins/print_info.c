/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 19:06:45 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/04 10:43:45 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

/**
 * @brief	Prints the current working directory
 * @returns	boolean true
**/

bool	builtin_pwd(void)
{
	char	*pwd;

	pwd = ft_getenv("PWD");
	printf("%s\n", pwd);
	free(pwd);
	return (true);
}

/**
 * @brief	Prints the environment variables of the system
 * @returns	boolean true
**/

bool	builtin_env(void)
{
	t_env	*current;
	t_list	*lst;

	lst = g_program.env;
	while (lst)
	{
		current = lst->content;
		printf("%s\n", current->full);
		lst = lst->next;
	}
	return (true);
}
