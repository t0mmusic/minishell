/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 19:06:45 by jbrown            #+#    #+#             */
/*   Updated: 2022/06/23 10:26:51 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

/*	Prints the current working directory.	*/

bool	builtin_pwd(void)
{
	char	buffer[512];

	ft_printf_fd("%s\n", 1, getcwd(buffer, sizeof(buffer)));
	return (true);
}

/*	Prints the environment variables of the system.	*/

bool	builtin_env(void)
{
	int		i;
	int		j;
	char	*env;

	i = 0;
	while (g_program.envp[i])
	{
		j = 0;
		while (g_program.envp[i][j] && g_program.envp[i][j] != '=')
			j++;
		env = ft_substr(g_program.envp[i], 0, j);
		if (!ft_strcmp("PWD", env))
		{
			ft_printf_fd("PWD=", 1);
			builtin_pwd();
		}
		else
		{
			ft_printf_fd("%s=%s\n", 1, env, getenv(env));
			free (env);
		}
		i++;
	}
	return (true);
}
