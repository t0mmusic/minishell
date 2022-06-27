/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 19:42:57 by jbrown            #+#    #+#             */
/*   Updated: 2022/06/27 11:14:35 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

void	init_global(void)
{
	g_program.envp = NULL;
	g_program.paths = ft_split(getenv("PATH"), ':');
	g_program.prompt = get_prompt();
	g_program.path = NULL;
	g_program.commands = NULL;
	g_program.cwd = NULL;
	g_program.root = NULL;
	g_program.user_inputs = NULL;
	g_program.exit_status = 0;
}
