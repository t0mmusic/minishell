/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 15:38:53 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/06 15:55:11 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

/**
 * @brief	Updates the char **envp in the global variable to match the linked
 * list of environment variables used by minishell.
**/

void	update_envp(void)
{
	int		size;
	int		i;
	char	**envp;
	t_list	*lst;
	t_env	*env;

	size = ft_lstsize(g_program.env);
	envp = malloc(sizeof(*envp) * size + 1);
	lst = g_program.env;
	i = 0;
	while (lst)
	{
		env = lst->content;
		if (env->silent == false)
		{
			envp[i] = env->full;
			i++;
		}
		lst = lst->next;
	}
	envp[i] = NULL;
	g_program.envp = envp;
}
