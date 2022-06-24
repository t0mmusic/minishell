/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:11:29 by jbrown            #+#    #+#             */
/*   Updated: 2022/06/24 12:17:14 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Frees the array of user inputs.	*/

void	free_inputs(char **inputs)
{
	int	i;

	if (!inputs)
		return ;
	i = 0;
	while (inputs[i])
	{
		free (inputs[i]);
		i++;
	}
	free (inputs);
}

/*	Frees a list. Only frees the list elements, not the content.	*/

void	freelist(t_list *list)
{
	t_list	*current;

	while (list)
	{
		current = list;
		list = list->next;
		free (current);
	}
}

/*	Frees a list. This also frees the malloced content contained in each
	list element.	*/

void	freelist_malloc(t_list *list)
{
	t_list	*current;

	while (list)
	{
		free (list->content);
		current = list;
		list = list->next;
		free (current);
	}
}
