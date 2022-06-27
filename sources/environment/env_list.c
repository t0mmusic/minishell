/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:22:12 by jbrown            #+#    #+#             */
/*   Updated: 2022/06/27 13:14:06 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

/*	Finds the matching list element selected for removal, then removes it.
	WIP*/

void	remove_env(char *str)
{
	t_list	*lst;
	t_list	*prev;
	t_env	*current;

	lst = g_program.env;
	prev = NULL;
	current = lst->content;
	while (lst->next)
	{
		if (ft_strcmp(str, current->var))
		{
			if (prev)
				prev->next = lst->next;
			else
				g_program.env = g_program.env->next;
			free_env(current);
			free(lst);
			return ;
		}
		prev = lst;
		lst = lst->next;
		current = lst->content;
	}
}

/*	Assigns all required values for the environment variable.	*/

void	edit_env(t_env *new, char *str, int split, bool silent)
{
	new->full = str;
	new->var = ft_substr(str, 0, split);
	new->content = ft_substr(str, split + 1, ft_strlen(&str[split]));
	new->silent = silent;
}

/*	Checks if the entered variable is new. If it is, it will save the value of
	the full string (variable and content), the seperate variable and content,
	and the boolean value indicating whether this is an environment variable
	or just a regular one. WIP.	*/

void	add_env(t_list **head, char *str, bool silent)
{
	t_env	*new;
	t_list	*lst;
	int		split;

	lst = *head;
	split = 0;
	while (str[split] && str[split] != '=')
		split++;
	while (lst)
	{
		new = lst->content;
		if (new->var && !ft_strncmp(new->var, str, split))
		{
			edit_env(new, str, split, silent);
			return ;
		}
		lst = lst->next;
	}
	new = malloc(sizeof(new) * 3);
	edit_env(new, str, split, silent);
	ft_lstadd_back(head, ft_lstnew(new));
}

/*	Initialises the list containing all of the environment variables.	*/

void	env_init(char **env)
{
	t_list	*env_list;

	env_list = NULL;
	while (*env)
	{
		add_env(&env_list, *env, false);
		env++;
	}
	g_program.env = env_list;
}
