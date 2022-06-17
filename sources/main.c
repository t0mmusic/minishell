/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:17:29 by Nathanael         #+#    #+#             */
/*   Updated: 2022/06/17 12:27:34 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	Function 'ft_printf_fd should be used for printing to make sure everything
	is output to the correct file.	*/

#include "minishell.h"

/*	Modify this function so that it ignores spaces after the name of
	a directory.	*/

bool	change_directory(char *str)
{
	char	*path;
	char	*gdir;
	char	*dir;
	char	*to;
	char	buf[1000];

	path = str + 2;
	while (*path == ' ')
		path++;
	gdir = getcwd(buf, sizeof(buf));
	dir = strcat(gdir, "/");
	to = strcat(dir, path);
	if (access(to, F_OK) < 0)
		ft_printf_fd("cd: Ain't no %s directory!\n", 1, path);
	else
		chdir(to);
	return (true);
}

/*	Checks if the user input is one of the recreated inbuilt functions.
	Each one of these should free the input string and make it NULL so
	that it does not pass through the 'out_process' function.	*/

bool	inbuilt_check(char *str)
{
	// if ("echo")
	// 	;
	if (!ft_strncmp("cd", str, 2))
		return (change_directory(str));
	// if ("pwd")
	// 	;
	// if ("export")
	// 	;
	// if ("unset")
	// 	;
	// if ("env")
	// 	;
	if (!ft_strcmp("exit", str))
		exit (0);
	return (false);
}

/*	Gives the user name and current directory for the prompt. This is updated
	each time the user enters a command.	NOTE: consider making the prompt
	part of the global variable so that it only updates when the current
	directory updates.	*/

char	*get_prompt(void)
{
	char	*prompt;
	char	*tmp;
	char	cwd[500];

	prompt = ft_strjoin("@minishell ", getcwd(cwd, sizeof(cwd)));
	tmp = prompt;
	prompt = ft_strjoin(tmp, " $ ");
	free (tmp);
	tmp = prompt;
	prompt = ft_strjoin(getenv("HOME") + 7, tmp);
	free(tmp);
	return (prompt);
}

int	main(int ac, char *argv[], char *envp[])
{
	char	*str;
	char	*prompt;
	t_prog	prog;

	check_args(ac, argv, envp);
//	print_env();
	prog.envp = envp;
	prog.paths = ft_split(getenv("PATH"), ':');
	while (1)
	{
		prompt = get_prompt();
		str = readline(prompt);
		add_history(str);
		//add a check to see if pipes and stuff are in the input
		if (inbuilt_check(str))
		{
			free(str);
			str = NULL;
		}
		if (str)
		{
			out_process(str, prog);
			free(str);
		}
		free(prompt);
	}
	return (0);
}
