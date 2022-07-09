/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 22:22:21 by Nathanael         #+#    #+#             */
/*   Updated: 2022/07/09 15:00:42 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BUFFER		10;

# ifndef S_IFDIR
#  define S_IFDIR 0040000
# endif
# ifndef S_IXUSR
#  define S_IXUSR 0000100
# endif

# define R_END 0
# define W_END 1

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
void	command(void);
void	next_command(void);

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
void	std_sort(char **commands);
int		check_file_access(char *file);
int		std_output(char *filename);
int		std_output_append(char *filename);
int		std_input(char *filename);
int		std_input_delim(char *filename);

/*	Signal Handling	*/
void	ctrl_handler(int sig);

/*	Environment	*/
void	env_init(char **env);
void	add_env(char *str, bool silent);
void	remove_env(char *str);
char	*ft_getenv(char *var);
void	update_envp(void);

/*	Token Handling	*/
bool	is_quotes(char *str);
char	*remove_quotes(char *str);
char	*sanitise_tokens(t_list *lst);
bool	is_bookend(char *str, int *current);
void	extra_token(t_list **lst, char *str, int *i);
char	*remove_str(char *s1, char *s2);
void	cpy_without(char *src, char *dst, int i, int len);
bool	and_or(char *token);
void	add_interp_token(t_list **lst, int *i, char *s1, char *s2);

/*	Utilities	*/
void	get_prompt(void);
int		ft_isspace(int c);
void	split_agrs(char *str);
bool	check_blank(char *str);
char	*expand_string(char *str);
int		ft_tryfree(void *ptr);
int		log_err(char *input, char *message, int ret);
char	*lst_to_str(char *str, t_list *lst);
char	*ft_ansii(char *str, char *colour);
char	*ft_free_join(char *s1, char *s2);
void	ft_lstall(t_list *lst, char *(*f)(char *));
void	iterate_user_inputs(void);
void	delete_lstelem(t_list **lst);

/*	Malloc/free	*/
void	free_inputs(void);
void	freelist(t_list *list);
void	freelist_malloc(t_list *list);
void	free_env(t_env *env);

/*	Initialisation	*/
void	init_global(void);
void	init_yesenv(char **av);
void	init_noenv(char **av);

/*	Error	*/
char	*error_code(void);
void	normalise_exit(void);

/*	Bonus	*/
char	*find_matches(char *str);
bool	interp_token(char *token);

#endif
