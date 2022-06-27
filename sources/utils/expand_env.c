/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:13:09 by jbrown            #+#    #+#             */
/*   Updated: 2022/06/27 17:22:46 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

/*	Takes all of the strings in a list and combines them into a single char
	array.	*/

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
		free (tmp);
		tmp = ret;
		lst = lst->next;
	}
	return (ret);
}

/*	Takes a piece of a string and extracts an environment variable. If there
	is no matching variable, it returns an empty string. Needs to be updated
	to use internal environment list.	*/

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
	if (!getenv(tmp))
		env = ft_strdup("");
	else
		env = ft_strdup(getenv(tmp));
	free (tmp);
	return (env);
}

/*	Converts the content of a list into a string if the list is
	full. Also frees the original string input by the user.	*/

char	*lst_to_str(char *str, t_list *lst)
{
	char	*tmp;
	t_list	*head;

	head = lst;
	if (lst->next)
	{
		tmp = str;
		str = join_list(lst);
		free (tmp);
	}
	freelist_malloc(head);
	return (str);
}

/*	Expands a string input by the user if it contains environment variables.
	It there are no evs, it remains the same.	*/

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
