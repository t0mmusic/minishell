/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 22:22:21 by Nathanael         #+#    #+#             */
/*   Updated: 2022/06/16 17:06:22 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "imported/libft.h"
# include "imported/ft_printf_fd.h"

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>

/**
 * @brief	Global environment
**/
typedef struct s_prog
{
	char	**envp;
	char	*path;
	char	*cwd;
	char	*root;
	char	**paths;
	char	**commands;
}	t_prog;

void	check_args(int argcount, char **argvect, char *envp[]);
void	print_env(void);

/*	Run processes	*/
void	out_process(char *str, t_prog prog);

#endif
