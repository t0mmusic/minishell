/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:11:29 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/02 16:29:46 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Frees an environment structure.	*/

void	free_env(t_env *env)
{
	ft_tryfree(env->var);
	ft_tryfree(env->content);
	ft_tryfree(env);
}

/*	Frees the array of user inputs.	*/

void	free_inputs(char **inputs)
{
	int	i;

	if (!inputs)
		return ;
	i = 0;
	while (inputs[i])
	{
		ft_tryfree(inputs[i]);
		i++;
	}
	ft_tryfree(inputs);
}

/*	Frees a list. Only frees the list elements, not the content.	*/

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

/*	Frees a list. This also frees the malloced content contained in each
	list element.	*/

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
