/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 19:42:57 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/04 12:38:26 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

/**
 * @brief	Initialises all elements of the global variable. Most are set to
 * NULL, paths is given an array of all paths from the environment variables
 * and prompt is given the user prompt.
**/

void	init_global(void)
{
	char	*shlvl;
	int		lvl;

	g_program.envp = NULL;
	g_program.paths = ft_split(getenv("PATH"), ':');
	shlvl = ft_getenv("SHLVL");
	lvl = ft_atoi(shlvl) + 1;
	free(shlvl);
	shlvl = ft_free_join(ft_strdup("SHLVL="), ft_itoa(lvl));
	add_env(shlvl, false);
	get_prompt();
	g_program.path = NULL;
	g_program.commands = NULL;
	g_program.cwd = NULL;
	g_program.root = NULL;
	g_program.user_inputs = NULL;
	g_program.exit_status = 0;
}
