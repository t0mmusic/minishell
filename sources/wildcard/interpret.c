/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 12:02:26 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/07 14:54:30 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

bool	and_or(char *token)
{
	if (!ft_strcmp(token, ";"))
		return (true);
	if (!ft_strcmp(token, "&&") && !g_program.exit_status)
		return (true);
	if (!ft_strcmp(token, "||") && g_program.exit_status)
		return (true);
	return (false);
}

void	next_command(void)
{
	char	*tmp;

	while (*g_program.user_inputs && !interp_token(*g_program.user_inputs))
	{
		tmp = *g_program.user_inputs;
		g_program.user_inputs++;
		free(tmp);
	}
	if (!*g_program.user_inputs)
		g_program.user_inputs = NULL;
	else
	{
		if (and_or(*g_program.user_inputs) == false)
		{
			g_program.user_inputs = NULL;
			return ;
		}
		tmp = *g_program.user_inputs;
		g_program.user_inputs++;
		free(tmp);
		if (*g_program.user_inputs)
			command();
	}
}

void	command(void)
{
	if (!inbuilt_check())
	{
		g_program.pid = fork();
		if (!g_program.pid)
		{
			check_pipes();
		}
		waitpid(g_program.pid, &g_program.exit_status, 0);
	}
	while (g_program.user_inputs)
		next_command();
}

bool	interp_token(char *token)
{
	if (!ft_strcmp(token, ";")
		|| !ft_strcmp(token, "||")
		|| !ft_strcmp(token, "&&"))
	{
		return (true);
	}
	return (false);
}
