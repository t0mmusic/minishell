/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nathanael <nervin@student.42adel.org.au    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:46:49 by Nathanael         #+#    #+#             */
/*   Updated: 2022/07/09 15:52:52 by Nathanael        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(int *fd, char *delim)
{
	char	*line;
	char	*tmp;
	int		i;

	i = 0;
	signal(SIGINT, heredoc_handler);
	line = readline("heredoc> ");
	while (line)
	{
		if (!ft_strncmp(line, delim, ft_strlen(delim) + 1) || \
			*(heredoc_signal_get()) == 1)
		{
			close(fd[W_END]);
			free(line);
			return ;
		}
		tmp = ft_strjoin(&line[i], "\n");
		ft_putstr_fd(&tmp[i], fd[W_END]);
		ft_tryfree(line);
		line = readline("heredoc> ");
		i++;
	}
	ft_tryfree(tmp);
	ft_tryfree(line);
	close(fd[W_END]);
}
