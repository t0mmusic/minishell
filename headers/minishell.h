/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 22:22:21 by Nathanael         #+#    #+#             */
/*   Updated: 2022/06/23 12:33:43 by jbrown           ###   ########.fr       */
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
	char	*prompt;
	char	*cwd;
	char	*root;
	char	**paths;
	char	**commands;
	char	**user_inputs;
}	t_prog;

/*	Declaration of global variable	*/
t_prog	g_program;

void	check_args(int argcount, char **argvect, char *envp[]);
void	print_env(void);

/*	Run processes	*/
void	out_process(void);
void	check_pipes(void);

/*	Inbuilt function recretations	*/
bool	inbuilt_check(void);
bool	inbuilt_subprocess(void);
bool	builtin_env(void);
bool	builtin_pwd(void);
bool	change_directory(void);
bool	builtin_echo(void);

/*	Standard input/output redirection	*/
void	std_sort(char *path, char *commands);
void	std_output(char *path, char *commands);
void	std_output_append(char *path, char *commands);
void	std_input(char *path, char *commands);
void	std_input_delim(char *path, char *commands);

/*	Utilities	*/
char	*get_prompt(void);
int		ft_isspace(int c);
char	*ft_get_cwd(void);
void	split_agrs(char *str);

/*	Malloc/free	*/
void	free_inputs(char **inputs);
void	freelist(t_list *list);

/*	Initialisation	*/
void	init_global(void);

#endif
