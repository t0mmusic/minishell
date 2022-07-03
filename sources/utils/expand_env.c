/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:13:09 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/03 15:25:50 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

/**
 * @brief	Finds the matching environment variable from the list in the global
 * variable. If there is no match, it returns an empty string instead.
 * @param	var: The variable name
 * @returns	matching varible content, or empty string if no match is found
**/

char	*ft_getenv(char *var)
{
	t_env	*env;
	t_list	*lst;

	lst = g_program.env;
	while (lst)
	{
		env = lst->content;
		if (!ft_strcmp(env->var, var))
		{
			return (ft_strdup(env->content));
		}
		lst = lst->next;
	}
	return (ft_strdup(""));
}

/**
 * @brief	Takes all of the strings in a list and combines them into a
 * single char array.
 * @param	lst: linked list of sanitised user inputs
 * @returns	ret: char array of combined user inputs
**/

char	*join_list(t_list *lst)
{
	char	*tmp;
	char	*ret;

	lst = lst->next;
	tmp = ft_strdup(lst->content);
	ret = tmp;
	while (lst->next)
	{
		ret = ft_strjoin(tmp, lst->next->content);
		ft_tryfree(tmp);
		tmp = ret;
		lst = lst->next;
	}
	return (ret);
}

/**
 * @brief	Takes a piece of a string and extracts an environment variable.
 * If there is no matching variable, it returns an empty string.
 * @param	str: The users input from the prompt
 * @param	*i: reference to current index of str
 * @param	*j: reference used to save beginning of current token
 * @returns	env: string of sanitised input
**/

char	*get_env(char *str, int *i, int *j)
{
	char	*env;
	char	*tmp;

	*i = *i + 1;
	while (str[*i] && (!ft_isspace(str[*i]) && str[*i] != '$'))
	{
		*i = *i + 1;
	}
	if (str[*j + 1] == '?' && *j + 2 == *i)
	{
		return (ft_itoa(g_program.exit_status));
	}
	*i = *i - 1;
	tmp = ft_substr(str, *j + 1, *i - *j);
	env = ft_strdup(ft_getenv(tmp));
	ft_tryfree(tmp);
	return (env);
}

/**
 * @brief	Converts the content of a list into a string if the list is full.
 * Also frees the original string input by the user.
 * @param	str: The users input from the prompt
 * @param	lst: list of sanitised user inputs (tokens)
 * @returns	str: newly tokenised string of user inputs
**/

char	*lst_to_str(char *str, t_list *lst)
{
	char	*tmp;
	t_list	*head;

	head = lst;
	if (lst->next)
	{
		tmp = str;
		str = join_list(lst);
		ft_tryfree(tmp);
	}
	freelist_malloc(head);
	return (str);
}

/**
 * @brief	Expands a string input by the user if it contains environment
 * variables. If there are no evs, it remains the same.
 * @param	str: The users input from the prompt
 * @returns	tokenised string of user inputs
**/

char	*expand_string(char *str)
{
	int		i;
	int		j;
	t_list	*strs;

	strs = ft_lstnew(ft_strdup("Head"));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			ft_lstadd_back(&strs, ft_lstnew(ft_substr(str, j, i - j)));
			j = i;
			ft_lstadd_back(&strs, ft_lstnew(get_env(str, &i, &j)));
			j = i + 1;
		}
		i++;
	}
	if (j <= i)
		ft_lstadd_back(&strs, ft_lstnew(ft_substr(str, j, i - j)));
	return (lst_to_str(str, strs));
}
