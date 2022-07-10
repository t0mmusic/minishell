/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:11:29 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/10 11:16:10 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Frees an environment structure, including all allocated pointers.
 * ! Need to evaluate what has to be freed here.
 * ! Might need to pass by reference
**/

void	free_env(t_list **lst)
{
	t_env	*env;
	t_list	*current;

	current = *lst;
	env = current->content;
	free(env->full);
	free(env->var);
	free(env->content);
	free(env);
}

void	free_full_env(void)
{
	t_list	*lst;

	lst = g_program.env;
	while (lst)
	{
		free_env(&lst);
		lst = lst->next;
	}
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
		free(g_program.user_inputs[i]);
		g_program.user_inputs[i] = NULL;
		i++;
	}
	free(g_program.user_inputs);
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
		free(current);
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
		free(list->content);
		current = list;
		list = list->next;
		free(current);
	}
}
