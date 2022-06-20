/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nathanael <nervin@student.42adel.org.au    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 22:22:21 by Nathanael         #+#    #+#             */
/*   Updated: 2022/06/20 11:02:07 by Nathanael        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BUFFER	10;

# include "imported/libft.h"
# include "ft_printf_fd.h"

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
bool	inbuilt_check(char *str);
void	check_pipes(char *str, t_prog prog);

/*	Inbuilt function recretations	*/
bool	inbuilt_check(char *str);
bool	inbuilt_subprocess(char *str, t_prog prog);
bool	builtin_env(t_prog prog);
bool	builtin_pwd(void);
bool	change_directory(char *str);

/*	Standard input/output redirection	*/
void	std_sort(char *path, char *commands);
void	std_output(char *path, char *commands);
void	std_output_append(char *path);
void	std_input(char *path);
void	std_input_delim(char *path);

/*	Utilities	*/
int		ft_isspace(int c);

#endif
