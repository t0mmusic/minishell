/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 22:22:21 by Nathanael         #+#    #+#             */
/*   Updated: 2022/07/04 21:02:16 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BUFFER		10;

# ifndef S_IFDIR
#  define S_IFDIR 0040000;
# endif
# ifndef S_IXUSR
#  define S_IXUSR 0000100;
# endif

# include "imported/libft.h"
# include "ft_printf_fd.h"
# include "colours.h"

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/ioctl.h>

/*	structure used for storing environment variables. Can also be used for
	regular shell variables if 'silent' is true.	*/

typedef struct s_env
{
	char	*full;
	char	*var;
	char	*content;
	bool	silent;
}	t_env;

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
	int		exit_status;
	int		pid;
	t_list	*env;
}	t_prog;

/*	Declaration of global variable	*/
t_prog	g_program;

void	program_loop(void);
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
bool	builtin_export(void);
bool	builtin_unset(void);

/*	Standard input/output redirection	*/
void	std_sort(char *path, char **commands);
int		check_file_access(char *file);
int		std_output(char *path, char *file);
int		std_output_append(char *path, char *file);
int		std_input(char *path, char *file);
int		std_input_delim(char *path, char *file);

/*	Signal Handling	*/
void	ctrl_handler(int sig);

/*	Environment	*/
void	env_init(char **env);
void	add_env(char *str, bool silent);
void	remove_env(char *str);
char	*ft_getenv(char *var);

/*	Utilities	*/
char	*get_prompt(void);
int		ft_isspace(int c);
void	split_agrs(char *str);
bool	check_blank(char *str);
char	*expand_string(char *str);
int		ft_tryfree(void *ptr);
int		log_err(char *input, char *message, int ret);
char	*lst_to_str(char *str, t_list *lst);
char	*ft_ansii(char *str, char *colour);
char	*ft_free_join(char *s1, char *s2);

/*	Malloc/free	*/
void	free_inputs(char **inputs);
void	freelist(t_list *list);
void	freelist_malloc(t_list *list);
void	free_env(t_env *env);

/*	Initialisation	*/
void	init_global(void);

/*	Bonus	*/
char	*find_matches(char *str);

#endif
