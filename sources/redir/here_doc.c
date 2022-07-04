/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nathanael <nervin@student.42adel.org.au    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:46:49 by Nathanael         #+#    #+#             */
/*   Updated: 2022/07/04 14:59:26 by Nathanael        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(char *delim, int *fd)
{
	char	*line;
	char	*temp;
	int		i;

	close(fd[R_END]);
	signal(SIGINT, handle_hd_sig);
	ft_putstr_fd("...", STDIN_FILENO);
	i = get_next_line(STDIN_FILENO, &line);
	while (i)
	{
		if (!ft_strncmp(line, delim, ft_strlen(delim) + 1) \
			|| *(get_signal_st() == 1))
		{
			close(fd[W_END]);
			free(line);
			return ;
		}
		temp = ft_strjoin(line, "\n");
		ft_putstr_fd(temp, fd[W_END]);
		free_tmp(tmp, line);
		ft_putstr_fd("... ", STDIN_FILENO);
		i = get_next_line(STDIN_FILENO, &line);
	}
	close(fd[W_END]);
	free(line);
}

