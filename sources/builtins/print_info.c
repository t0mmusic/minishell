/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 19:06:45 by jbrown            #+#    #+#             */
/*   Updated: 2022/06/17 19:50:02 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	builtin_pwd(void)
{
	ft_printf_fd("%s\n", 1, getenv("PWD"));
	return (true);
}

bool	builtin_env(void)
{
	printf("[[SHELL: %s]]\n", getenv("SHELL"));
	printf("[[NAME: %s]]\n", getenv("NAME"));
	printf("[[PWD: %s]]\n", getenv("PWD"));
	printf("[[LOGNAME: %s]]\n", getenv("LOGNAME"));
	printf("[[MOTD_SHOWN: %s]]\n", getenv("MOTD_SHOWN"));
	printf("[[HOME: %s]]\n", getenv("HOME"));
	printf("[[LANG: %s]]\n", getenv("LANG"));
	printf("[[TERM: %s]]\n", getenv("TERM"));
	printf("[[USER: %s]]\n", getenv("USER"));
	printf("[[XDG_DATA_DIRS: %s]]\n", getenv("XDG_DATA_DIRS"));
	printf("[[PATH: %s]]\n", getenv("PATH"));
	printf("[[HOSTTYPE: %s]]\n", getenv("HOSTTYPE"));
	printf("[[OLDPWD: %s]]\n", getenv("OLDPWD"));
	printf("[[ROOT: %s]]\n", getenv("ROOT"));
	return (true);
}
