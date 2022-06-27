/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:01:59 by jbrown            #+#    #+#             */
/*   Updated: 2022/06/27 12:54:41 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

t_list	*lst_cpy(t_list *src)
{
	t_list	*dst;

	dst = NULL;
	while (src)
	{
		ft_lstadd_back(&dst, ft_lstnew(src->content));
		src = src->next;
	}
	return (dst);
}

/*	Adds a new environment variable. Not updatating the global variable for
	reasons unknown. WIP.	*/

bool	builtin_export(void)
{
	t_list	*tmp;

	tmp = lst_cpy(g_program.env);
	add_env(&tmp, g_program.user_inputs[1], false);
	g_program.env = NULL;
	return (true);
}

/*	Removes an environment variable if it exists. WIP.	*/

bool	builtin_unset(void)
{
	remove_env(g_program.user_inputs[1]);
	return (true);
}
