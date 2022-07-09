/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 14:56:01 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/09 15:00:00 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

void	add_interp_token(t_list **lst, int *i, char *s1, char *s2)
{
	int	len;

	len = ft_strlen(s2);
	if (!ft_strncmp(&s1[*i], s2, len))
	{
		ft_lstadd_back(lst, ft_lstnew(ft_strdup(s2)));
		*i += len;
	}
}
