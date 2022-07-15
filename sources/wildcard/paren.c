/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paren.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:27:09 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/15 10:40:31 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

static bool	parend_check(void)
{
	char	*str;
	int		i;

	if (!g_program.user_inputs[1])
		return (false);
	str = g_program.user_inputs[1];
	i = 0;
	while (str[i])
	{
		if (str[i] == ')')
			return (true);
		i++;
	}
	return (false);
}

static char	*next_paren(char *arr)
{
	char	*sub;
	int		i;

	i = 0;
	while (arr[i] && arr[i] != ')')
		i++;
	i++;
	if (!arr[i])
	{
		free(arr);
		return (NULL);
	}
	sub = ft_substr(arr, i, ft_strlen(arr) - i);
	free(arr);
	return (sub);
}

static void	parent_paren(void)
{
	char	*str;

	str = ft_strdup(g_program.user_inputs[1]);
	str = next_paren(str);
	free_array(g_program.user_inputs);
	if (str)
	{
		split_agrs(str);
		wild_token();
	}
	else
		g_program.user_inputs = NULL;
	waitpid(g_program.pid, &g_program.exit_status, 0);
	next_command();
}

void	parentheses(void)
{
	char	*str;

	if (!parend_check())
	{
		ft_printf_fd("Missing ')'!\n", 2);
		free_array(g_program.user_inputs);
		g_program.user_inputs = NULL;
		return ;
	}
	g_program.pid = fork();
	if (!g_program.pid)
	{
		str = ft_strdup(g_program.user_inputs[1]);
		free_array(g_program.user_inputs);
		split_agrs(str);
		wild_token();
		g_program.user_inputs = realloc_front(g_program.user_inputs, ")");
		if (g_program.user_inputs)
			command();
		normalise_exit();
		free_exit(g_program.exit_status);
	}
	parent_paren();
}
