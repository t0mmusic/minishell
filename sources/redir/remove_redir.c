/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 13:10:35 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/13 20:47:18 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

void	error_redir(char *type)
{
	int	i;

	i = 0;
	while (g_program.user_inputs[i]
		&& ft_strcmp(g_program.user_inputs[i], type))
		i++;
	if (!g_program.user_inputs[i + 1])
	{
		ft_printf_fd("minishell: Redirect missing!\n", 2);
		free_exit(2);
	}
}

void	remove_redir(char *type)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	while (g_program.user_inputs[i])
		i++;
	new = malloc(sizeof(*new) * (i - 1));
	i = 0;
	j = 0;
	while (g_program.user_inputs[i])
	{
		if (!ft_strcmp(g_program.user_inputs[i], type))
			i += 2;
		if (!g_program.user_inputs[i])
			break ;
		new[j++] = ft_strdup(g_program.user_inputs[i++]);
	}
	new[j] = NULL;
	free_array(g_program.user_inputs);
	g_program.user_inputs = new;
}
