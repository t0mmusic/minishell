/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:17:29 by Nathanael         #+#    #+#             */
/*   Updated: 2022/06/16 14:49:04 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_list(t_prog *prog)
{
	prog->paths = ft_split(getenv("PATH"), ':');
}

void	change_directory(char *path)
{
	char	*gdir;
	char	*dir;
	char	*to;
	char	buf[1000];

	path += 2;
	while (*path == ' ')
		path++;
	gdir = getcwd(buf, sizeof(buf));
    dir = strcat(gdir, "/");
    to = strcat(dir, path);
	chdir(to);
}

char	*get_prompt(void)
{
	char	*prompt;
	char	*tmp;
	char	cwd[500];

	prompt = ft_strjoin("@minishell ", getcwd(cwd, sizeof(cwd)));
	tmp = prompt;
	prompt = ft_strjoin(tmp, " % ");
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
	init_list(&prog);
	while (1)
	{
		prompt = get_prompt();
		str = readline(prompt);
		add_history(str);
		if (!ft_strcmp("exit", str))
			break ;
		if (!ft_strncmp("cd", str, 2))
			change_directory(str);
		else
			out_process(str, prog, argv, envp);
		free(str);
		free(prompt);
	}
	return (0);
}
