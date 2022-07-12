/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 10:13:07 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/12 21:31:01 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Compares two strings in reverse for length len.
 * @param	s1: first string to be compared
 * @param	s2: second string to be compared
 * @param	len: no. of bytes that the strings will be compared
 * @returns	difference between two strings at point where they differ or at len
 * bytes
**/

int	ft_strnrcmp(const char *s1, const char *s2, size_t len)
{
	int	i;
	int	j;

	i = ft_strlen(s1) - 1;
	j = ft_strlen(s2) - 1;
	while (i >= 0 && j >= 0 && s1[i] == s2[j] && len - 1)
	{
		i--;
		j--;
		len--;
	}
	return (s1[i] - s2[j]);
}

/**
 * @brief	Returns a value based on the type of wildcard.
 * @param	str: The users input from the prompt
 * @returns	:
 * 0 for wild with no conditions.
 * 1 for wild at end of string.
 * 2 for wild at beginning of string.
 * 3 for wild in middle of string.
**/

int	check_wild(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '*' && !str[i + 1])
	{
		return (0);
	}
	if (str[i] == '*')
	{
		return (1);
	}
	while (str[i])
	{
		if (str[i] == '*' && str[i + 1])
		{
			return (3);
		}
		i++;
	}
	return (2);
}

/**
 * @brief	Splits the string in half at the * and then checks files in
 * the directory for matches of both. If they do, it adds them to the
 * back of the list.
 * @param	str: The users input from the prompt
 * @param	lst: list of all matches
 * @returns	lst: the complete list of matches
**/

t_list	*multi_match(char *str, t_list *lst)
{
	char			**comp;
	struct dirent	*p_dirent;
	DIR				*p_dir;
	char			*pwd;

	pwd = ft_getenv("PWD");
	p_dir = opendir(pwd);
	free(pwd);
	p_dirent = readdir(p_dir);
	comp = ft_split(str, '*');
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("<WILD> ")));
	while (p_dirent)
	{
		if (!ft_strncmp(str, p_dirent->d_name, ft_strlen(comp[0]))
			&& !ft_strnrcmp(str, p_dirent->d_name, ft_strlen(comp[1])))
			ft_lstadd_back(&lst, ft_lstnew(ft_strjoin(p_dirent->d_name, " ")));
		p_dirent = readdir(p_dir);
	}
	closedir(p_dir);
	free_array(comp);
	return (lst);
}

/**
 * @brief	Adds matching files to list. If the * is at the beginning of the
 * string it compares the end of the string. If the * is at the end, it compares
 * the beginning of the string.
 * @param	str: The users input from the prompt
 * @param	lst: list of matches
 * @param	f: input function, either strncmp or strnrcmp
 * @returns	lst of matches
**/

t_list	*add_match(char *str, t_list *lst,
	int f(const char *, const char *, size_t))
{
	struct dirent	*p_dirent;
	DIR				*p_dir;
	bool			flag;
	char			*pwd;

	pwd = ft_getenv("PWD");
	p_dir = opendir(pwd);
	free(pwd);
	p_dirent = readdir(p_dir);
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("<WILD> ")));
	while (p_dirent)
	{
		if (!f(str, p_dirent->d_name, ft_strlen(str) - 1))
		{
			ft_lstadd_back(&lst, ft_lstnew(ft_strjoin(p_dirent->d_name, " ")));
			flag = true;
		}
		else
			flag = false;
		p_dirent = readdir(p_dir);
	}
	closedir(p_dir);
	return (lst);
}

/**
 * @brief	Finds matching files based on different criteria.
 * @param	str: The users input from the prompt
 * @returns	new string of matches
 * ! modify this so that it takes in a string and the token list
 * ! removes the original token and replaces it with this list.
**/

char	*find_matches(char *str)
{
	t_list	*matches;
	int		wild;

	if (!ft_strchr(str, '*') || is_quotes(str))
		return (str);
	matches = NULL;
	wild = check_wild(str);
	if (wild == 1)
	{
		matches = add_match(str, matches, ft_strnrcmp);
	}
	if (wild == 2)
	{
		matches = add_match(str, matches, ft_strncmp);
	}
	if (wild == 3)
	{
		matches = multi_match(str, matches);
	}
	if (!matches)
	{
		ft_printf_fd("minishell: no matches found for %s", 2, str);
		return (ft_strdup(""));
	}
	return (lst_to_str(str, matches));
}
