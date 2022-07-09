/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 19:42:57 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/09 19:07:19 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

/**
 * @brief	Adds an environment variable with stringjoin
 * @param	var: variable name of environment variable
 * @param	content: content of environment variable
 * @param	silent: boolean value to indicate environment variable status
**/

void	add_env_easy(char *var, char *content, bool silent)
{
	char	*tmp;

	tmp = ft_strjoin(var, content);
	add_env(tmp, silent);
	free(tmp);
}

/**
 * @brief	If there is no environment passed into minishell, this will set
 * some default values.
 * @param	av: argument variable used to get the name of the program
 * ! has an issue with the prompt, unsure why at this time
**/

void	init_noenv(char **av)
{
	g_program.env = NULL;
	add_env_easy("SHELL=", av[0], false);
	add_env_easy("PWD=", getcwd(NULL, 0), false);
	add_env("LOGNAME=guest", false);
	add_env("USER=guest", false);
	add_env("SHLVL=1", false);
	add_env("TERM=xterm-256color", false);
	add_env("PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin",
		false);
	add_env_easy("_=", av[0], false);
	get_prompt();
}

/**
 * @brief	If there is an environment passed into minishell, it is used here
 * to set up basic values.
 * @param	av: argument variable used to get the name of the program
**/

void	init_yesenv(char **av)
{
	char	*shlvl;
	int		lvl;

	add_env_easy("SHELL=", av[0], false);
	g_program.paths = ft_split(getenv("PATH"), ':');
	add_env_easy("PWD=", getcwd(NULL, 0), false);
	shlvl = ft_getenv("SHLVL");
	lvl = ft_atoi(shlvl) + 1;
	free(shlvl);
	shlvl = ft_free_join(ft_strdup("SHLVL="), ft_itoa(lvl));
	add_env(shlvl, false);
}

/**
 * @brief	Initialises all elements of the global variable. Most are set to
 * NULL, paths is given an array of all paths from the environment variables
 * and prompt is given the user prompt.
**/

void	init_global(void)
{
	g_program.envp = NULL;
	g_program.path = NULL;
	g_program.commands = NULL;
	g_program.cwd = NULL;
	g_program.root = NULL;
	g_program.user_inputs = NULL;
	g_program.exit_status = 0;
}
