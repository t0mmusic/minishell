/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 10:38:33 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/08 11:13:25 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

/**
 * @brief	Checks a string from a ' or a " to see if it has a match.
 * @param	str: The users input from the prompt
 * @param	current: current index of str
 * @returns	boolean true if match is found, false if not
**/

bool	is_bookend(char *str, int *current)
{
	char	bookend;
	int		i;

	i = *current;
	if (str[i] != '\'' && str[i] != '\"')
		return (true);
	if (!str[i + 1])
		return (false);
	bookend = str[i];
	i += 1;
	while (str[i])
	{
		if (str[i] == bookend)
			return (true);
		i++;
	}
	*current += 1;
	return (false);
}

int	is_quotes(char *str)
{
	if (str[0] == '\'')
		return (2);
	if (str[0] == '\"')
		return (1);
	return (0);
}

char	*remove_quotes(char *str)
{
	char	end;
	char	*ret;
	int		i;

	if (!is_quotes(str))
		return (str);
	i = 0;
	end = str[i];
	i++;
	while (str[i] && str[i] != end)
		i++;
	ret = ft_substr(str, 1, i - 1);
	if (end == '\"')
		return (expand_string(ret));
	return (ret);
}

char	*sanitise_tokens(t_list *lst)
{
	t_list	*head;

	head = lst;
	while (lst)
	{
		lst->content = find_matches(lst->content);
		lst = lst->next;
	}
	lst = head;
	while (lst)
	{
		lst->content = expand_string(lst->content);
		lst = lst->next;
	}
	lst = head;
	while (lst)
	{
		lst->content = remove_quotes(lst->content);
		lst = lst->next;
	}
	return (lst_to_str(ft_strdup(""), head));
}
