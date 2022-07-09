/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:11:29 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/09 11:28:38 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Frees an environment structure, including all allocated pointers.
 * ! Need to evaluate what has to be freed here.
**/

void	free_env(t_env *env)
{
	ft_tryfree(env->var);
	ft_tryfree(env->content);
	ft_tryfree(env);
}

/**
 * @brief	Frees the array of user inputs.
 * @param	inputs: An array of sanitised user inputs
**/

void	free_inputs(void)
{
	int	i;

	if (!g_program.user_inputs)
		return ;
	i = 0;
	while (g_program.user_inputs[i])
	{
		ft_tryfree(g_program.user_inputs[i]);
		g_program.user_inputs[i] = NULL;
		i++;
	}
	ft_tryfree(g_program.user_inputs);
	g_program.user_inputs = NULL;
}

/**
 * @brief	Frees all list elements of a list. Not for freeing list content
**/

void	freelist(t_list *list)
{
	t_list	*current;

	while (list)
	{
		current = list;
		list = list->next;
		ft_tryfree(current);
	}
}

/**
 * @brief	Frees all list elements and content from a list
**/

void	freelist_malloc(t_list *list)
{
	t_list	*current;

	while (list)
	{
		ft_tryfree(list->content);
		current = list;
		list = list->next;
		ft_tryfree(current);
	}
}
