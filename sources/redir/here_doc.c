/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:46:49 by Nathanael         #+#    #+#             */
/*   Updated: 2022/07/11 14:23:24 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(int fd, char *delim)
{
	char	*line;
	char	*tmp;

	signal(SIGINT, heredoc_handler);
	line = readline("heredoc> ");
	while (line)
	{
		if (!ft_strncmp(line, delim, ft_strlen(delim) + 1) || \
			*(heredoc_signal_get()) == 1)
		{
			close(fd);
			free(line);
			return ;
		}
		tmp = ft_strjoin(line, "\n");
		ft_putstr_fd(tmp, fd);
		free(line);
		line = readline("heredoc> ");
	}
	free(tmp);
	free(line);
}
