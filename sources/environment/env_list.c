/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:22:12 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/10 10:42:10 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

/**
 * @brief	Finds the matching list element selected for removal, then removes it
 * @param	str: a string matching the name of an evironment variable
**/

void	remove_env(char *str)
{
	t_list	*lst;
	t_list	*prev;
	t_env	*current;

	lst = g_program.env;
	prev = NULL;
	current = lst->content;
	while (lst)
	{
		if (!ft_strcmp(str, current->var))
		{
			if (prev)
				prev->next = lst->next;
			else
				g_program.env = g_program.env->next;
			free_env(&lst);
			free(lst);
			return ;
		}
		prev = lst;
		lst = lst->next;
		if (lst)
			current = lst->content;
	}
}

/**
 * @brief	Assigns all required values for the environment variable.
 * @param	new: environment variable structure
 * @param	str: The full environment variable, variable and content
 * @param	split: integer variable of the index of the '='
 * @param	silent: boolean value indicating whether to print with 'env'
**/

void	edit_env(t_list **lst, char *str, int split, bool silent)
{
	t_env	*env;
	t_list	*current;

	current = *lst;
	env = malloc(sizeof(*env) * (sizeof(char *) * 3 + sizeof(bool)));
	env->full = ft_strdup(str);
	env->var = ft_substr(str, 0, split);
	env->content = ft_substr(str, split + 1, ft_strlen(&str[split]));
	env->silent = silent;
	current->content = env;
}

/**
 * @brief	Checks if the entered variable is new. If it is, it will save the
 * value of the full string (variable and content), the seperate variable and
 * content, and the boolean value indicating whether this is an environment
 * variable or just a regular one.
 * @param	str: Name of environment variable
 * @param	silent: boolean value indicating whether to print with 'env'
 * ! Consider using split instead of searching for '='
 * ! Needs to account for strings in quotes
**/

void	add_env(char *str, bool silent)
{
	t_env	*new;
	t_list	*lst;
	int		split;

	lst = g_program.env;
	split = 0;
	while (str[split] && str[split] != '=')
		split++;
	while (lst)
	{
		new = lst->content;
		if (new->var && !ft_strncmp(new->var, str, split))
		{
			free_env(&lst);
			edit_env(&lst, str, split, silent);
			return ;
		}
		lst = lst->next;
	}
	lst = ft_lstnew(NULL);
	edit_env(&lst, str, split, silent);
	ft_lstadd_back(&g_program.env, lst);
}

/**
 * @brief	Initialises the list containing all of the environment variables.
 * @param	env: array of system environment variables
**/

void	env_init(char **env)
{
	if (!env)
		return ;
	while (*env)
	{
		add_env(*env, false);
		env++;
	}
}
