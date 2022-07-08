/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 10:38:33 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/08 15:55:27 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

/**
 * @brief	Removes uninterpreted characters from tokens
 * @param	token: the token being processed
 * @returns	the processed token
 * * removes '|', '\', '&&' and '||' from tokens
**/

char	*trim_token(char *token)
{
	if (is_quotes(token))
		return (token);
	token = remove_str(token, "\\");
	token = remove_str(token, ";");
	token = remove_str(token, "&&");
	token = remove_str(token, "||");
	return (token);
}

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

/**
 * @brief	Checks if the first value of a string is a ' or a "
 * @param	str: the current token
 * @returns	boolean true if match is found, false if not
**/

bool	is_quotes(char *str)
{
	if (str[0] == '\'' || str[0] == '\"')
		return (true);
	return (false);
}

/**
 * @brief	Removes quotes from the ends of a token
 * @param	str: the current token
 * @returns	the token sans quotes
**/

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

/**
 * @brief	Takes list of broken token and compiles it into a single
 * string with the appropriate values.
 * @param	lst: the list containing token fragments
 * @returns	rebuilt token
**/

char	*sanitise_tokens(t_list *lst)
{
	ft_lstall(lst, find_matches);
	ft_lstall(lst, expand_string);
	ft_lstall(lst, trim_token);
	ft_lstall(lst, remove_quotes);
	return (lst_to_str(ft_strdup(""), lst));
}
